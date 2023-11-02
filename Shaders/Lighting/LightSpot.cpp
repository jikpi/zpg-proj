//
// Created by KOP0269 on 11/2/23.
//

#include "LightSpot.h"
#include "../../Application/Configuration/AGlobalConfig.h"
#include "glm/geometric.hpp"

LightSpot::LightSpot(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &color, float intensity,
                     float constant, float linear, float quadratic, float cutOff, float outerCutOff)
        : RenderableLight(
        LIGHT_TYPE_SPOT, color, intensity),

          Position(position),
          Direction(glm::normalize(direction)),
          Constant(constant),
          Linear(linear),
          Quadratic(quadratic),
          InnerCutOff(cutOff),
          OuterCutOff(outerCutOff) {

}

LightSpot::LightSpot(const glm::vec3 &position, const glm::vec3 &direction)
        : RenderableLight(
        LIGHT_TYPE_SPOT),

          Position(position),
          Direction(glm::normalize(direction)),
          Constant(DEF_LIGHT_CONSTANT),
          Linear(DEF_LIGHT_LINEAR),
          Quadratic(DEF_LIGHT_QUADRATIC),
          InnerCutOff(DEF_LIGHT_INNERCUTOFF),
          OuterCutOff(DEF_LIGHT_OUTERCUTOFF) {

}

LightSpot & LightSpot::SetPosition(const glm::vec3 &newPosition) {
    Position = newPosition;
    return *this;
}

LightSpot & LightSpot::SetDirection(const glm::vec3 &newDirection) {
    Direction = glm::normalize(newDirection);
    return *this;
}

LightSpot & LightSpot::SetConstant(float newConstant) {
    Constant = newConstant;
    return *this;
}

LightSpot & LightSpot::SetLinear(float newLinear) {
    Linear = newLinear;
    return *this;
}

LightSpot & LightSpot::SetQuadratic(float newQuadratic) {
    Quadratic = newQuadratic;
    return *this;
}

LightSpot & LightSpot::SetInnerCutOff(float newInnerCutOff) {
    InnerCutOff = newInnerCutOff;
    return *this;
}

LightSpot & LightSpot::SetOuterCutOff(float newOuterCutOff) {
    OuterCutOff = newOuterCutOff;
    return *this;
}

const glm::vec3 &LightSpot::GetPosition() const {
    return Position;
}

const glm::vec3 &LightSpot::GetDirection() const {
    return Direction;
}

float LightSpot::GetConstant() const {
    return Constant;
}

float LightSpot::GetLinear() const {
    return Linear;
}

float LightSpot::GetQuadratic() const {
    return Quadratic;
}

float LightSpot::GetInnerCutOff() const {
    return InnerCutOff;
}

float LightSpot::GetOuterCutOff() const {
    return OuterCutOff;
}
