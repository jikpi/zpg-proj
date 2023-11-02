//
// Created by KOP0269 on 11/2/23.
//

#ifndef ZPG_TEST_LIGHTSPOT_H
#define ZPG_TEST_LIGHTSPOT_H


#include "Abstract/RenderableLight.h"

class LightSpot : public RenderableLight {
private:
    glm::vec3 Position{};
    glm::vec3 Direction{};

    float Constant;
    float Linear;
    float Quadratic;

    float InnerCutOff;
    float OuterCutOff;

public:
    LightSpot(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &color, float intensity,
              float constant, float linear, float quadratic, float cutOff, float outerCutOff);

    LightSpot(const glm::vec3 &position, const glm::vec3 &direction);

    LightSpot & SetPosition(const glm::vec3 &newPosition);
    LightSpot & SetDirection(const glm::vec3 &newDirection);
    LightSpot & SetConstant(float newConstant);
    LightSpot & SetLinear(float newLinear);
    LightSpot & SetQuadratic(float newQuadratic);
    LightSpot & SetInnerCutOff(float newInnerCutOff);
    LightSpot & SetOuterCutOff(float newOuterCutOff);

    [[nodiscard]] const glm::vec3 &GetPosition() const;
    [[nodiscard]] const glm::vec3 &GetDirection() const;
    [[nodiscard]] float GetConstant() const;
    [[nodiscard]] float GetLinear() const;
    [[nodiscard]] float GetQuadratic() const;
    [[nodiscard]] float GetInnerCutOff() const;
    [[nodiscard]] float GetOuterCutOff() const;
};


#endif //ZPG_TEST_LIGHTSPOT_H
