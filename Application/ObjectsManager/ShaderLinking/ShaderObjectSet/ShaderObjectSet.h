//
// Created by KOP0269 on 10/20/23.
//

#ifndef ZPG_TEST_SHADEROBJECTSET_H
#define ZPG_TEST_SHADEROBJECTSET_H

#include <memory>
#include <vector>


#include "../../../../Model/StandardisedModel.h"
#include "../../../../Shaders/ShaderProgram/ShaderHandler.h"

class ShaderObjectSet {
public:
    explicit ShaderObjectSet(std::shared_ptr<ShaderHandler> shader);
    std::shared_ptr<ShaderHandler> Shader;
    std::vector<std::shared_ptr<StandardisedModel>> Objects;
    std::shared_ptr<StandardisedModel> Skybox;
};


#endif //ZPG_TEST_SHADEROBJECTSET_H
