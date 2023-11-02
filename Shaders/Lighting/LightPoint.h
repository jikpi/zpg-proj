//
// Created by KOP0269 on 10/20/23.
//

#ifndef ZPG_TEST_LIGHTPOINT_H
#define ZPG_TEST_LIGHTPOINT_H


#include "glm/vec3.hpp"
#include "Abstract/RenderableLight.h"

class LightPoint : public RenderableLight{
private:
    glm::vec3 Position{};

    float Constant;
    float Linear;
    float Quadratic;

public:
    LightPoint(const glm::vec3 &position, const glm::vec3 &color, float intensity, float constant,
               float linear, float quadratic);
    LightPoint(const glm::vec3 &position, const glm::vec3 &color);
    explicit LightPoint(const glm::vec3 &position);

    void SetPosition(const glm::vec3 &newPosition);
    void SetConstant(float newConstant);
    void SetLinear(float newLinear);
    void SetQuadratic(float newQuadratic);

    [[nodiscard]] const glm::vec3 &GetPosition() const;
    [[nodiscard]] float GetConstant() const;
    [[nodiscard]] float GetLinear() const;
    [[nodiscard]] float GetQuadratic() const;
};


#endif //ZPG_TEST_LIGHTPOINT_H
