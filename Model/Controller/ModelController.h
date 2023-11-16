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

class ModelController {
private:
    enum ModelType {
        Any,
        PositionNormalTex,
        PositionNormal,
        Position
    };

    struct ModelData {
        std::vector<float> Data;
        ModelType Type;
    };

    std::map<std::string, ModelData> ModelsData;

    static ModelController::ModelData LoadModel(const std::string &path);

    std::shared_ptr<StandardisedModel>
    RetrieveModel(const std::string &path, ModelController::ModelType type, const std::string &Name, bool standardPath);
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
