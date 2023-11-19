//
// Created by lvi on 11/16/23.
//

#ifndef ZPG_TEST_MODELCONTROLLER_H
#define ZPG_TEST_MODELCONTROLLER_H


#include <vector>
#include <string>
#include <map>
#include <memory>
#include "../StandardisedModel.h"
#include "../../Model/ModelStamp.h"

class ModelController {
private:

    struct ModelData {
        std::vector<float> Data;
        ModelStamp Type;
        bool HasMaterial;
        Material material;
    };

    std::map<std::string, std::vector<ModelData>> ModelsData;

    static std::vector<ModelData> LoadModel(const std::string &path);

    std::shared_ptr<StandardisedModel>
    RetrieveModel(const std::string &path, ModelStamp type, const std::string &Name, bool anyType,
                  bool standardPath);
public:
    std::shared_ptr<StandardisedModel>
    UsePositionNormalTex(const std::string &path, const std::string &Name = "None", bool standardPath = true);
    std::shared_ptr<StandardisedModel>
    UsePositionNormal(const std::string &path, const std::string &Name = "None", bool standardPath = true);
    std::shared_ptr<StandardisedModel>
    UsePosition(const std::string &path, const std::string &Name = "None", bool standardPath = true);
    std::shared_ptr<StandardisedModel>
    UseAny(const std::string &path, const std::string &Name = "None", bool standardPath = true);
};


#endif //ZPG_TEST_MODELCONTROLLER_H
