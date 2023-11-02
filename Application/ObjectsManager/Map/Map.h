//
// Created by KOP0269 on 10/6/23.
//

#ifndef ZPG_TEST_MAP_H
#define ZPG_TEST_MAP_H


#include <vector>
#include <memory>
#include "../../../Model/Abstract/BaseModelData.h"
#include "../../../Model/StandardisedModel.h"
#include "../../../Shaders/Lighting/Light.h"

class Map {
    std::string Name;

    std::vector<std::shared_ptr<StandardisedModel>> Objects;
    std::shared_ptr<std::vector<std::shared_ptr<Light>>> Lights;
public:
    explicit Map(std::string name = "None");
    friend class MapToShaderLinker;



    void InsertObject(const std::shared_ptr<StandardisedModel>& object);
    unsigned long GetObjectCount();
    std::shared_ptr<StandardisedModel> & GetObject(int index);
    std::shared_ptr<StandardisedModel> &GetObjectByName(const std::string &name);

    void InsertLight(const std::shared_ptr<Light>& light);
    unsigned long GetLightCount();
    std::shared_ptr<Light> & GetLight(int index);
    void ChangeLight(int index, const std::shared_ptr<Light>& light);


    [[nodiscard]] std::string GetName() const;
};


#endif //ZPG_TEST_MAP_H
