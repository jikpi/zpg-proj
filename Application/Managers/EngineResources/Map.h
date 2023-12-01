//
// Created by KOP0269 on 10/6/23.
//

#ifndef ZPG_TEST_MAP_H
#define ZPG_TEST_MAP_H


#include <vector>
#include <memory>
#include "../../../Model/Abstract/BaseModelData.h"
#include "../../../Model/StandardisedModel.h"
#include "../../../Shaders/Lighting/LightPoint.h"

class Map {
    std::string Name;

    std::vector<std::shared_ptr<StandardisedModel>> Objects;
    std::shared_ptr<std::vector<std::shared_ptr<RenderableLight>>> Lights;
    std::shared_ptr<StandardisedModel> Skybox;

    void InsertLight(const std::shared_ptr<RenderableLight> &light);
    unsigned long GetLightCount();
    std::shared_ptr<RenderableLight> &MasterGetLight(int index);
    void ChangeLight(int index, const std::shared_ptr<RenderableLight> &light);
    void SetSkybox(const std::shared_ptr<StandardisedModel> &skybox);
    void InsertObject(const std::shared_ptr<StandardisedModel> &object);
public:
    explicit Map(std::string name = "None");

    friend class MapToShaderLinker;

    friend class ResourcesManager;

    unsigned long GetObjectCount();
    [[nodiscard]] const std::shared_ptr<StandardisedModel> &GetSkybox() const;

    std::shared_ptr<StandardisedModel> &GetObject(int index);
    std::shared_ptr<StandardisedModel> &GetObject(const std::string &name);

    std::shared_ptr<RenderableLight> &GetLight(const std::string &lightName);

    static void RemoveObject(StandardisedModel* object);


    [[nodiscard]] std::string GetName() const;
};


#endif //ZPG_TEST_MAP_H
