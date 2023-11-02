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

    void SetPosition(const glm::vec3 &newPosition) override;
    void SetConstant(float newConstant) override;
    void SetLinear(float newLinear) override;
    void SetQuadratic(float newQuadratic) override;

    [[nodiscard]] const glm::vec3 &GetPosition() const override;
    [[nodiscard]] float GetConstant() const override;
    [[nodiscard]] float GetLinear() const override;
    [[nodiscard]] float GetQuadratic() const override;
};


#endif //ZPG_TEST_LIGHTPOINT_H
