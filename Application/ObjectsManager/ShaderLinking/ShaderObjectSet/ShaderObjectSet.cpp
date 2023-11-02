//
// Created by KOP0269 on 10/20/23.
//

#include "ShaderObjectSet.h"

#include <utility>

ShaderObjectSet::ShaderObjectSet(std::shared_ptr<ShaderHandler> shader) {
    Shader = std::move(shader);
}
