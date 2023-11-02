//
// Created by KOP0269 on 10/27/23.
//

#ifndef ZPG_TEST_RENDERABLEOBJECT_H
#define ZPG_TEST_RENDERABLEOBJECT_H


#include "glm/ext/matrix_float4x4.hpp"
#include "../Material.h"

class RenderableObject {
public:
    virtual ~RenderableObject() = default;
    [[nodiscard]] virtual glm::mat4 GetTransf() const = 0;
    [[nodiscard]] virtual Material GetMaterial() const = 0;
};


#endif //ZPG_TEST_RENDERABLEOBJECT_H
