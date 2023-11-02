//
// Created by KOP0269 on 10/6/23.
//

#ifndef ZPG_TEST_MODELFACTORY_H
#define ZPG_TEST_MODELFACTORY_H


#include <memory>
#include "../Abstract/BaseModelData.h"
#include "../StandardisedModel.h"

class ModelFactory {
public:
    static std::shared_ptr<StandardisedModel> PositionNormal(const float *model, int size, std::string Name = "None");
    static std::shared_ptr<StandardisedModel> XYZ_Model(const float *model, int size, std::string Name = "None");

};


#endif //ZPG_TEST_MODELFACTORY_H