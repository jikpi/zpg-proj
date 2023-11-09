//
// Created by KOP0269 on 10/28/23.
//

#ifndef ZPG_TEST_MAPMANAGER_H
#define ZPG_TEST_MAPMANAGER_H


#include <memory>
#include "Map.h"
#include "../ShaderLinking/MapToShaderLinker.h"
#include "../../../Model/Texture/Controller/TextureController.h"

class MapManager {
private:



    void MasterAddObjectToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel>& object);
    void MasterAddLightToMap(std::shared_ptr<Map> &map, const std::shared_ptr<RenderableLight>& light);
    std::shared_ptr<Map> ActiveMap;
    std::vector<std::shared_ptr<Map>> Maps;
public:
    void Initialize();
    void ForceRefreshMaps();
    MapToShaderLinker ShaderLinker;
    void SetFallbackShader(std::shared_ptr<ShaderHandler> &shader);

    std::shared_ptr<Map> & GetMapByName(const std::string &name);
    std::shared_ptr<Map>& GetMapByIndex(int index);
    std::shared_ptr<Map>& GetActiveMap();

    void CreateNewMap(const std::string &name);
    void InsertMap(const std::shared_ptr<Map> &map);

    void AddObjectToMap(int mapIndex, const std::shared_ptr<StandardisedModel>& object);
    void AddObjectToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel>& object);
    void AddObjectToMap(const std::string &mapName, const std::shared_ptr<StandardisedModel>& object);
    void AddObjectToCurrentMap(const std::shared_ptr<StandardisedModel>& object);

    void AddLightToMap(int index, const std::shared_ptr<RenderableLight>& light);
    void AddLightToMap(std::shared_ptr<Map> &map, const std::shared_ptr<RenderableLight>& light);
    void AddLightToMap(const std::string &name, const std::shared_ptr<RenderableLight>& light);
    void AddLightToCurrentMap(const std::shared_ptr<RenderableLight>& light);

    void AddSkyboxToMap(int index, const std::shared_ptr<StandardisedModel>& skybox);
    void AddSkyboxToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel>& skybox);
    void AddSkyboxToMap(const std::string &name, const std::shared_ptr<StandardisedModel>& skybox);
    void AddSkyboxToCurrentMap(const std::shared_ptr<StandardisedModel>& skybox);

    void ForceRefreshLightsOnCurrentMap();
    std::shared_ptr<RenderableLight> & GetLightOnMap(int mapIndex, int lightIndex);
    std::shared_ptr<RenderableLight> & GetLightOnMap(const std::string &mapName, int lightIndex);

    void ChangeLightOnMap(int mapIndex, int lightIndex, const std::shared_ptr<RenderableLight>& light);
    void ChangeLightOnMap(const std::string &mapName, int lightIndex, const std::shared_ptr<RenderableLight>& light);

    void ChangeMap(std::shared_ptr<Map> &map);
    void ChangeMap(int index);
    void ChangeMap(const std::string &name);
};


#endif //ZPG_TEST_MAPMANAGER_H
