//
// Created by KOP0269 on 11/2/23.
//

#ifndef ZPG_TEST_RENDERABLELIGHT_H
#define ZPG_TEST_RENDERABLELIGHT_H


#include "glm/vec3.hpp"
#include "LightType.h"

class RenderableLight {
protected:
    glm::vec3 Color{};
    float Intensity{};

    LightType Type;
public:
    RenderableLight(LightType type, const glm::vec3 &color, float intensity);
    explicit RenderableLight(LightType type, const glm::vec3 &color);
    explicit RenderableLight(LightType type, float intensity);
    explicit RenderableLight(LightType type);

    [[nodiscard]] const glm::vec3 &GetColor() const;
    [[nodiscard]] float GetIntensity() const;
    [[nodiscard]] LightType GetType() const;

    void SetColor(const glm::vec3 &newColor);
    void SetIntensity(float newIntensity);
};


#endif //ZPG_TEST_RENDERABLELIGHT_H
