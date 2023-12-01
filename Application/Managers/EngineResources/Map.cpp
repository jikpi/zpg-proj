//
// Created by KOP0269 on 10/6/23.
//

#include "Map.h"

#include <utility>
#include <iostream>

Map::Map(std::string name) {
    this->Name = std::move(name);
    Lights = std::make_shared<std::vector<std::shared_ptr<RenderableLight>>>();
}

std::string Map::GetName() const {
    return Name;
}

void Map::InsertObject(const std::shared_ptr<StandardisedModel> &object) {
    Objects.push_back(object);
}

std::shared_ptr<StandardisedModel> &Map::GetObject(const int index) {

    if (index >= Objects.size()) {
        std::cerr << "ERROR: Map: Object index not found." << std::endl;
        throw std::runtime_error("ERROR: Map: Object index not found.");
    }

    return Objects.at(index);
}

std::shared_ptr<StandardisedModel> &Map::GetObject(const std::string &name) {
    for (auto &object: Objects) {
        if (object->Name() == name) {
            return object;
        }
    }

    std::cerr << "ERROR: Map: Object with name \"" << name << "\" not found. Returning any." << std::endl;
    return GetObject(0);
}

unsigned long Map::GetObjectCount() {
    return Objects.size();
}

void Map::InsertLight(const std::shared_ptr<RenderableLight> &light) {
    Lights->push_back(light);

}

unsigned long Map::GetLightCount() {
    return Lights->size();
}

std::shared_ptr<RenderableLight> &Map::MasterGetLight(int index) {
    if(index >= Lights->size()) {
        std::cerr << "ERROR: Map: Light index not found, map name: " << this->Name << std::endl;
        throw std::runtime_error("ERROR: Map: Light index not found.");
    }

    return Lights->at(index);
}

void Map::ChangeLight(int index, const std::shared_ptr<RenderableLight> &light) {
    Lights->at(index) = light;
}

void Map::SetSkybox(const std::shared_ptr<StandardisedModel> &skybox) {
    if (this->Skybox != nullptr) {
        std::cerr << "WARNING: Map: Skybox on map '" << this->Name << "' already set, overriding with object: "
                  << skybox->Name() << std::endl;
    }
    this->Skybox = skybox;
}

const std::shared_ptr<StandardisedModel> &Map::GetSkybox() const {
    return this->Skybox;
}
