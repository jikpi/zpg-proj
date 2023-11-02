//
// Created by KOP0269 on 10/20/23.
//

#include <iostream>
#include "MapToShaderLinker.h"

MapToShaderLinker::MapToShaderLinker() {
    ShaderObjectSets = std::vector<std::shared_ptr<ShaderObjectSet>>();
}

void MapToShaderLinker::AddShader(const std::shared_ptr<ShaderHandler> &shader) {
    ShaderObjectSets.push_back(std::make_shared<ShaderObjectSet>(shader));
}

void MapToShaderLinker::SetFallbackShader(std::shared_ptr<ShaderHandler> &shader) {
    this->FallbackShader = shader;
}

void
MapToShaderLinker::AddObjectToShader(std::shared_ptr<ShaderHandler> &shader,
                                     const std::shared_ptr<StandardisedModel> &object) {
    for (auto &set: ShaderObjectSets) {
        if (set->Shader == shader) {
            set->Objects.push_back(object);
            return;
        }
    }

    std::cerr << "ShaderProgramLinker: Shader not found when trying to: AddObjectToShader" << std::endl;
}

void MapToShaderLinker::AddObjectToShaderWithName(const std::string &name, std::shared_ptr<StandardisedModel> &object) {
    for (auto &set: ShaderObjectSets) {
        if (set->Shader->Name == name) {
            set->Objects.push_back(object);
            return;
        }
    }

    std::cerr << "ShaderProgramLinker: Shader not found when trying to: AddObjectToShaderWithName" << std::endl;
}

void MapToShaderLinker::PrintBuildingObjectError(const std::shared_ptr<StandardisedModel> &object) {
    std::cerr << "WARNING: ShaderProgramLinker: Object of name \"" << object->Name() <<
              "\" of stamp \"" << object->Stamp() <<
              "\" in the selected map has no shader program; Trying to use fallback shader;" << std::endl;
}

bool MapToShaderLinker::TryUseFallbackShader() {
    if (this->FallbackShader.expired()) {
        std::cerr << "ERROR: ShaderProgramLinker: Fallback shader not set. Object ignored." << std::endl;
        return false;
    } else {
        return true;
    }
}

void MapToShaderLinker::LinkLightsToShader(std::shared_ptr<ShaderHandler> &shader, const std::shared_ptr<Map> &map) {
    for (auto &set: ShaderObjectSets) {
        set->Shader->SetLights(map->Lights);
    }
}

void MapToShaderLinker::BuildWithMap(const std::shared_ptr<Map> &map) {

    this->ShaderObjectSets.clear();

    for (auto &object: map->Objects) {

        std::shared_ptr<ShaderHandler> objectsShader = object->GetShaderProgram().lock();
        if (objectsShader == nullptr) {
            this->PrintBuildingObjectError(object);
            if (this->TryUseFallbackShader()) {
                objectsShader = this->FallbackShader.lock();
            } else {
                continue;
            }
        }

        bool containsShader = false;
        for (auto &set: this->ShaderObjectSets) {
            if (set->Shader == objectsShader) {
                containsShader = true;
                set->Objects.push_back(object);
                break;
            }
        }
        if (!containsShader) {
            this->AddShader(objectsShader);
            this->AddObjectToShader(objectsShader, object);
        }

    }

    for (auto &set: this->ShaderObjectSets) {
        set->Shader->SetLights(map->Lights);
    }
}

void MapToShaderLinker::BuildWithMapSingleObject(const std::shared_ptr<Map> &map,
                                                 const std::shared_ptr<StandardisedModel> &object) {
    std::shared_ptr<ShaderHandler> objectsShader = object->GetShaderProgram().lock();
    if (objectsShader == nullptr) {
        PrintBuildingObjectError(object);
        if (this->TryUseFallbackShader()) {
            objectsShader = this->FallbackShader.lock();
        } else {
            return;
        }
    }

    bool containsShader = false;
    for (auto &set: this->ShaderObjectSets) {
        if (set->Shader == objectsShader) {
            containsShader = true;
            set->Objects.push_back(object);
            break;
        }
    }
    if (!containsShader) {
        this->AddShader(objectsShader);
        this->AddObjectToShader(objectsShader, object);
    }
}

void MapToShaderLinker::NotifyLightsOnCurrentMapChanged() {
    for (auto &set: this->ShaderObjectSets) {
        set->Shader->NotifyLightsChanged();
    }
}

