//
// Created by KOP0269 on 10/28/23.
//

#include <iostream>
#include "ResourcesManager.h"
#include "../../Configuration/AGlobalConfig.h"

void ResourcesManager::Initialize(bool addDefaultMap) {
    if (addDefaultMap) {
        this->Maps.push_back(std::make_shared<Map>(DEF_MAP_NAME));
        this->ChangeMap(0);

        MapCacheName = DEF_MAP_NAME;
        MapCacheIndex = 0;
    }

}

void ResourcesManager::ForceRefreshMaps() {
    //Refresh map
    this->ShaderLinker.BuildWithMap(this->ActiveMap);

    //Reset shader units
    TextureObjectsController.ResetTextureUnitCounter();

    //Connect logic to map
    this->ActiveGameLogic = nullptr;
    bool found = false;
    for (auto &logic: this->GameLogics) {
        if (this->ActiveMap->Name == logic->GetMapName()) {
            this->ActiveGameLogic = logic.get();
            found = true;
            break;
        }
    }

    if (!found) {
        std::cerr << "WARNING: ResourcesManager: No logic found for map: " << this->ActiveMap->Name << std::endl;
    }
}

void ResourcesManager::CreateNewMap(const std::string &name) {
    this->Maps.push_back(std::make_shared<Map>(name));
}

void ResourcesManager::InsertMap(const std::shared_ptr<Map> &map) {

    if (map == nullptr) {
        std::cerr << "ERROR: MapManager: Map is null." << std::endl;
        return;
    }

    this->Maps.push_back(map);
}

std::shared_ptr<Map> &ResourcesManager::GetMap(const int index) {

    if (this->Maps.empty()) {
        std::cerr << "ERROR: MapManager: No maps found." << std::endl;
        throw std::runtime_error("No maps found.");
    }

    if (index >= this->Maps.size() || index < 0) {
        std::cerr << "ERROR: MapManager: Map index not found:" << index << std::endl;
        return this->Maps.at(0);
    }

    return this->Maps.at(index);
}

std::shared_ptr<Map> &ResourcesManager::GetMap(const std::string &name) {
    if (name == MapCacheName) {
        return this->Maps.at(MapCacheIndex);
    }

    for (int i = 0; i < this->Maps.size(); i++) {
        if (this->Maps.at(i)->GetName() == name) {
            MapCacheName = name;
            MapCacheIndex = i;
            return this->Maps.at(i);
        }
    }

    std::cerr << "ERROR: MapManager: Map name \"" << name << "\" not found." << std::endl;
    return GetMap(0);
}

std::shared_ptr<Map> &ResourcesManager::GetActiveMap() {
    return this->ActiveMap;
}

void ResourcesManager::ChangeMap(std::shared_ptr<Map> &map) {
    this->ActiveMap = map;

    //Refresh shader linker
    ForceRefreshMaps();
}

void ResourcesManager::ChangeMap(int index) {
    //By index
    if (index >= this->Maps.size()) {
        std::cerr << "ERROR: MapManager: Map index not found: " << index << std::endl;
        return;
    }

    this->ActiveMap = this->Maps.at(index);

    //Refresh shader linker
    ForceRefreshMaps();
}

void ResourcesManager::ChangeMap(const std::string &name) {
    //By name
    std::shared_ptr<Map> &map = this->GetMap(name);
    this->ActiveMap = map;

    //Refresh shader linker
    ForceRefreshMaps();
}

// Objects ##########################################################################################################
void
ResourcesManager::MasterAddObjectToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel> &object) {
    map->InsertObject(object);
    if (map == this->ActiveMap) {
        ShaderLinker.BuildWithMapSingleObject(map, object);
    }
}

void ResourcesManager::AddObjectToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel> &object) {
    this->MasterAddObjectToMap(map, object);
}

void ResourcesManager::AddObjectToMap(int mapIndex, const std::shared_ptr<StandardisedModel> &object) {
    this->MasterAddObjectToMap(GetMap(mapIndex), object);
}

void ResourcesManager::AddObjectToMap(const std::string &mapName, const std::shared_ptr<StandardisedModel> &object) {
    std::shared_ptr<Map> &map = this->GetMap(mapName);
    this->MasterAddObjectToMap(map, object);
}

void ResourcesManager::AddObjectToCurrentMap(const std::shared_ptr<StandardisedModel> &object) {
    this->MasterAddObjectToMap(this->ActiveMap, object);
}

// Lights ############################################################################################################

void ResourcesManager::MasterAddLightToMap(std::shared_ptr<Map> &map, const std::shared_ptr<RenderableLight> &light) {
    map->InsertLight(light);
    if (map == this->ActiveMap) {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }
}

void ResourcesManager::AddLightToMap(std::shared_ptr<Map> &map, const std::shared_ptr<RenderableLight> &light) {
    this->MasterAddLightToMap(map, light);
}

void ResourcesManager::AddLightToMap(int index, const std::shared_ptr<RenderableLight> &light) {
    this->MasterAddLightToMap(GetMap(index), light);
}

void ResourcesManager::AddLightToCurrentMap(const std::shared_ptr<RenderableLight> &light) {
    this->MasterAddLightToMap(this->ActiveMap, light);
}

void ResourcesManager::AddLightToMap(const std::string &name, const std::shared_ptr<RenderableLight> &light) {
    std::shared_ptr<Map> &map = this->GetMap(name);
    this->MasterAddLightToMap(map, light);
}

std::shared_ptr<RenderableLight> &ResourcesManager::GetLightOnMap(int mapIndex, int lightIndex) {
    std::shared_ptr<Map> &map = this->GetMap(mapIndex);
    std::shared_ptr<RenderableLight> &light = map->GetLight(lightIndex);

    if (map == this->ActiveMap) {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }

    return light;
}

void ResourcesManager::ChangeLightOnMap(int mapIndex, int lightIndex, const std::shared_ptr<RenderableLight> &light) {
    std::shared_ptr<Map> &map = this->GetMap(mapIndex);
    map->ChangeLight(lightIndex, light);

    if (map == this->ActiveMap) {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }
}

void ResourcesManager::SetFallbackShader(std::shared_ptr<ShaderHandler> &shader) {
    this->ShaderLinker.SetFallbackShader(shader);
}

std::shared_ptr<RenderableLight> &ResourcesManager::GetLightOnMap(const std::string &mapName, int lightIndex) {
    std::shared_ptr<Map> &map = this->GetMap(mapName);
    std::shared_ptr<RenderableLight> &light = map->GetLight(lightIndex);

    if (map == this->ActiveMap) {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }

    return light;
}

std::shared_ptr<RenderableLight> &ResourcesManager::GetLightOnMap(std::shared_ptr<Map> &map, int lightIndex) {
    std::shared_ptr<RenderableLight> &light = map->GetLight(lightIndex);

    if (map == this->ActiveMap) {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }

    return light;
}

void ResourcesManager::ChangeLightOnMap(const std::string &mapName, int lightIndex,
                                        const std::shared_ptr<RenderableLight> &light) {
    std::shared_ptr<Map> &map = this->GetMap(mapName);
    map->ChangeLight(lightIndex, light);

    if (map == this->ActiveMap) {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }
}

void ResourcesManager::ForceRefreshLightsOnCurrentMap() {
    ShaderLinker.NotifyLightsOnCurrentMapChanged();
}

void ResourcesManager::AddSkyboxToMap(int index, const std::shared_ptr<StandardisedModel> &skybox) {
    std::shared_ptr<Map> &map = this->GetMap(index);
    map->SetSkybox(skybox);
}

void ResourcesManager::AddSkyboxToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel> &skybox) {
    map->SetSkybox(skybox);
}

void ResourcesManager::AddSkyboxToMap(const std::string &name, const std::shared_ptr<StandardisedModel> &skybox) {
    std::shared_ptr<Map> &map = this->GetMap(name);
    map->SetSkybox(skybox);
}

void ResourcesManager::AddSkyboxToCurrentMap(const std::shared_ptr<StandardisedModel> &skybox) {
    this->ActiveMap->SetSkybox(skybox);
}

StandardisedModel *ResourcesManager::GetObjectByContextID(unsigned short contextID) {
    return this->ShaderLinker.GetObjectByContextID(contextID);
}

void ResourcesManager::MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button,
                                             int action, int mods) const {
    if (this->ActiveGameLogic == nullptr) {
        return;
    }
    this->ActiveGameLogic->MouseCursorClickEvent(xCursorCoords, yCursorCoords, windowHeight, windowWidth, button, action, mods);
}

void ResourcesManager::KeyPressEvent(int key, int scancode, int action, int mods) const {
    if (this->ActiveGameLogic == nullptr) {
        return;
    }

    this->ActiveGameLogic->KeyPressEvent(key, scancode, action, mods);
}
