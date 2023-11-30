//
// Created by KOP0269 on 10/28/23.
//

#ifndef ZPG_TEST_RESOURCESMANAGER_H
#define ZPG_TEST_RESOURCESMANAGER_H


#include <memory>
#include "Map.h"
#include "../ShaderLinking/MapToShaderLinker.h"
#include "../../../Model/Texture/Controller/TextureController.h"
#include "../../../Model/Controller/ModelController.h"
#include "../../GameLogic/Abstract/AnyGameLogic.h"

class AnyGameLogic;

class ResourcesManager {
private:
    std::string MapCacheName;
    int MapCacheIndex;

    void MasterAddObjectToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel> &object);
    void MasterAddLightToMap(std::shared_ptr<Map> &map, const std::shared_ptr<RenderableLight> &light);
    std::shared_ptr<Map> ActiveMap;
    std::vector<std::shared_ptr<Map>> Maps;
public:
    void Initialize(bool addDefaultMap);
    void ForceRefreshMaps();
    MapToShaderLinker ShaderLinker;
    void SetFallbackShader(std::shared_ptr<ShaderHandler> &shader);

    TextureController TextureObjectsController;
    ModelController ModelObjectController;

    std::shared_ptr<Map> &GetMap(const std::string &name);
    std::shared_ptr<Map> &GetMap(int index);
    std::shared_ptr<Map> &GetActiveMap();

    void CreateNewMap(const std::string &name);
    void InsertMap(const std::shared_ptr<Map> &map);

    void AddObjectToMap(int mapIndex, const std::shared_ptr<StandardisedModel> &object);
    void AddObjectToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel> &object);
    void AddObjectToMap(const std::string &mapName, const std::shared_ptr<StandardisedModel> &object);
    void AddObjectToCurrentMap(const std::shared_ptr<StandardisedModel> &object);

    void AddLightToMap(int index, const std::shared_ptr<RenderableLight> &light);
    void AddLightToMap(std::shared_ptr<Map> &map, const std::shared_ptr<RenderableLight> &light);
    void AddLightToMap(const std::string &name, const std::shared_ptr<RenderableLight> &light);
    void AddLightToCurrentMap(const std::shared_ptr<RenderableLight> &light);

    void AddSkyboxToMap(int index, const std::shared_ptr<StandardisedModel> &skybox);
    static void AddSkyboxToMap(std::shared_ptr<Map> &map, const std::shared_ptr<StandardisedModel> &skybox);
    void AddSkyboxToMap(const std::string &name, const std::shared_ptr<StandardisedModel> &skybox);
    void AddSkyboxToCurrentMap(const std::shared_ptr<StandardisedModel> &skybox);

    void ForceRefreshLightsOnCurrentMap();
    std::shared_ptr<RenderableLight> &GetLightOnMap(int mapIndex, int lightIndex);
    std::shared_ptr<RenderableLight> &GetLightOnMap(const std::string &mapName, int lightIndex);
    std::shared_ptr<RenderableLight> &GetLightOnMap(std::shared_ptr<Map> &map, int lightIndex);

    void ChangeLightOnMap(int mapIndex, int lightIndex, const std::shared_ptr<RenderableLight> &light);
    void ChangeLightOnMap(const std::string &mapName, int lightIndex, const std::shared_ptr<RenderableLight> &light);

    void ChangeMap(std::shared_ptr<Map> &map);
    void ChangeMap(int index);
    void ChangeMap(const std::string &name);

    StandardisedModel *GetObjectByContextID(unsigned short contextID);

    template<typename T, typename U>
    std::shared_ptr<StandardisedModel> &GetObjectOnMap(T mapTemplate, U objectTemplate) {
        static_assert(std::is_integral<T>::value || std::is_same<T, const char *>::value, "T must be an int or string");
        static_assert(std::is_integral<U>::value || std::is_same<U, const char *>::value,
                      "U must be an int or a string");

        std::shared_ptr<Map> &map = this->GetMap(mapTemplate);
        std::shared_ptr<StandardisedModel> &object = map->GetObject(objectTemplate);

        return object;
    }

    AnyGameLogic *CurrentGameLogic{};
    void
    MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button, int action,
                          int mods) const;

    void KeyPressEvent(int key, int scancode, int action, int mods) const;
};


#endif //ZPG_TEST_RESOURCESMANAGER_H
