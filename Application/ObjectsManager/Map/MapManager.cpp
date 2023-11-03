//
// Created by KOP0269 on 10/28/23.
//

#include <iostream>
#include "MapManager.h"
#include "../../Configuration/AGlobalConfig.h"

void MapManager::Initialize() {
    this->Maps.push_back(std::make_shared<Map>(DEF_MAP_NAME));
    this->ChangeMap(0);
}

void MapManager::ForceRefreshMaps() {
    this->ShaderLinker.BuildWithMap(this->ActiveMap);
}

void MapManager::CreateNewMap(const std::string &name) {
    this->Maps.push_back(std::make_shared<Map>(name));
}

void MapManager::InsertMap(const std::shared_ptr<Map> &map) {
    this->Maps.push_back(map);
}

std::shared_ptr<Map> &MapManager::GetMapByIndex(int index) {
    if (index >= this->Maps.size()) {
        std::cerr << "ERROR: MapManager: Map index not found." << std::endl;
        return this->Maps.at(0);
    }
    return this->Maps.at(index);
}

std::shared_ptr<Map> &MapManager::GetMapByName(const std::string &name) {
    for (auto &map: this->Maps) {
        if (map->GetName() == name) {
            return map;
        }
    }
    std::cerr << "ERROR: MapManager: Map name \"" << name << "\" not found." << std::endl;
    return this->Maps.at(0);
}

std::shared_ptr<Map> &MapManager::GetActiveMap() {
    return this->ActiveMap;
}

void MapManager::ChangeMap(std::shared_ptr<Map> &map) {
    this->ActiveMap = map;

    //Refresh shader linker
    ForceRefreshMaps();
}

void MapManager::ChangeMap(int index) {
    //By index
    if (index >= this->Maps.size()) {
        std::cerr << "ERROR: MapManager: Map index not found." << std::endl;
        return;
    }

    this->ActiveMap = this->Maps.at(index);

    //Refresh shader linker
    ForceRefreshMaps();
}

void MapManager::ChangeMap(const std::string &name) {
    //By name
    std::shared_ptr<Map> &map = this->GetMapByName(name);
    this->ActiveMap = map;

    //Refresh shader linker
    ForceRefreshMaps();
}

// Objects ##########################################################################################################
void
MapManager::MasterAddObjectToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel> &object) {
    map->InsertObject(object);
    if (map == this->ActiveMap) {
        ShaderLinker.BuildWithMapSingleObject(map, object);
    }
}

void MapManager::AddObjectToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel> &object) {
    this->MasterAddObjectToMap(map, object);
}

void MapManager::AddObjectToMap(int mapIndex, const std::shared_ptr<StandardisedModel> &object) {
    this->MasterAddObjectToMap(GetMapByIndex(mapIndex), object);
}

void MapManager::AddObjectToMap(const std::string &mapName, const std::shared_ptr<StandardisedModel> &object) {
    std::shared_ptr<Map> &map = this->GetMapByName(mapName);
    this->MasterAddObjectToMap(map, object);
}

void MapManager::AddObjectToCurrentMap(const std::shared_ptr<StandardisedModel> &object) {
    this->MasterAddObjectToMap(this->ActiveMap, object);
}

// Lights ############################################################################################################

void MapManager::MasterAddLightToMap(std::shared_ptr<Map> &map, const std::shared_ptr<RenderableLight> &light) {
    map->InsertLight(light);
    if (map == this->ActiveMap) {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }
}

void MapManager::AddLightToMap(std::shared_ptr<Map> &map, const std::shared_ptr<RenderableLight> &light) {
    this->MasterAddLightToMap(map, light);
}

void MapManager::AddLightToMap(int index, const std::shared_ptr<RenderableLight> &light) {
    this->MasterAddLightToMap(GetMapByIndex(index), light);
}

void MapManager::AddLightToCurrentMap(const std::shared_ptr<RenderableLight> &light) {
    this->MasterAddLightToMap(this->ActiveMap, light);
}

void MapManager::AddLightToMap(const std::string &name, const std::shared_ptr<RenderableLight> &light) {
    std::shared_ptr<Map> &map = this->GetMapByName(name);
    this->MasterAddLightToMap(map, light);
}

std::shared_ptr<RenderableLight> & MapManager::GetLightOnMap(int mapIndex, int lightIndex) {
    std::shared_ptr<Map> &map = this->GetMapByIndex(mapIndex);
    std::shared_ptr<RenderableLight> &light = map->GetLight(lightIndex);

    if(map == this->ActiveMap)
    {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }

    return light;
}

void MapManager::ChangeLightOnMap(int mapIndex, int lightIndex, const std::shared_ptr<RenderableLight> &light) {
    std::shared_ptr<Map> &map = this->GetMapByIndex(mapIndex);
    map->ChangeLight(lightIndex, light);

    if(map == this->ActiveMap)
    {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }
}

void MapManager::SetFallbackShader(std::shared_ptr<ShaderHandler> &shader) {
    this->ShaderLinker.SetFallbackShader(shader);
}

std::shared_ptr<RenderableLight> &MapManager::GetLightOnMap(const std::string &mapName, int lightIndex) {
    std::shared_ptr<Map> &map = this->GetMapByName(mapName);
    std::shared_ptr<RenderableLight> &light = map->GetLight(lightIndex);

    if(map == this->ActiveMap)
    {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }

    return light;
}

void MapManager::ChangeLightOnMap(const std::string &mapName, int lightIndex,
                                  const std::shared_ptr<RenderableLight> &light) {
    std::shared_ptr<Map> &map = this->GetMapByName(mapName);
    map->ChangeLight(lightIndex, light);

    if(map == this->ActiveMap)
    {
        ShaderLinker.NotifyLightsOnCurrentMapChanged();
    }
}

void MapManager::ForceRefreshLightsOnCurrentMap() {
    ShaderLinker.NotifyLightsOnCurrentMapChanged();
}
