//
// Created by KOP0269 on 11/2/23.
//

#ifndef ZPG_TEST_RENDERABLELIGHT_H
#define ZPG_TEST_RENDERABLELIGHT_H


#include "glm/vec3.hpp"
#include "LightType.h"
#include "../../../Model/Abstract/RenderableObject.h"

class RenderableLight {
private:
protected:
    glm::vec3 Color{};
    float Intensity{};

    LightType Type;
public:
    RenderableLight(LightType type, const glm::vec3 &color, float intensity);
    explicit RenderableLight(LightType type, const glm::vec3 &color);
    explicit RenderableLight(LightType type, float intensity);
    explicit RenderableLight(LightType type);
    RenderableLight();
    virtual ~RenderableLight() = default;

    [[nodiscard]] const glm::vec3 &GetColor() const;
    [[nodiscard]] float GetIntensity() const;
    [[nodiscard]] LightType GetType() const;

    RenderableLight &SetColor(const glm::vec3 &newColor);
    RenderableLight &SetIntensity(float newIntensity);
};


#endif //ZPG_TEST_RENDERABLELIGHT_H
