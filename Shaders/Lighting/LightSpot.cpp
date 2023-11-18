//
// Created by KOP0269 on 11/2/23.
//

#include "LightSpot.h"
#include "../../Application/Configuration/AGlobalConfig.h"

LightSpot::LightSpot(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &color, float intensity,
                     float constant, float linear, float quadratic, float cutOff, float outerCutOff)
        : RenderableLight(
        LIGHT_TYPE_SPOT, color, intensity),

          Position(position),
          Direction(glm::normalize(direction)),
          Constant(constant),
          Linear(linear),
          Quadratic(quadratic) {

    InnerCutOff = glm::cos(glm::radians(cutOff));
    OuterCutOff = glm::cos(glm::radians(outerCutOff));

    if (InnerCutOff <= OuterCutOff) {
        InnerCutOff = OuterCutOff + 0.001f;
    }

    if (OuterCutOff >= InnerCutOff) {
        OuterCutOff = InnerCutOff - 0.001f;
    }
}

LightSpot::LightSpot(const glm::vec3 &position, const glm::vec3 &direction)
        : LightSpot(position,
                    direction,
                    DEF_LIGHT_COLOR,
                    DEF_LIGHT_INTENSITY,
                    DEF_LIGHT_CONSTANT,
                    DEF_LIGHT_LINEAR,
                    DEF_LIGHT_QUADRATIC,
                    DEF_LIGHT_INNERCUTOFF,
                    DEF_LIGHT_OUTERCUTOFF) {

}

LightSpot &LightSpot::SetPosition(const glm::vec3 &newPosition) {
    Position = newPosition;
    return *this;
}

LightSpot &LightSpot::SetDirection(const glm::vec3 &newDirection) {
    Direction = glm::normalize(newDirection);
    return *this;
}

LightSpot &LightSpot::SetConstant(float newConstant) {
    Constant = newConstant;
    return *this;
}

LightSpot &LightSpot::SetLinear(float newLinear) {
    Linear = newLinear;
    return *this;
}

LightSpot &LightSpot::SetQuadratic(float newQuadratic) {
    Quadratic = newQuadratic;
    return *this;
}

LightSpot &LightSpot::SetInnerCutOff(float newInnerCutOff) {
    float tempInner = glm::cos(glm::radians(newInnerCutOff));
    if (tempInner <= OuterCutOff) {
        tempInner = OuterCutOff + 0.001f;
    }

    InnerCutOff = tempInner;
    return *this;
}

LightSpot &LightSpot::SetOuterCutOff(float newOuterCutOff) {
    float tempOuter = glm::cos(glm::radians(newOuterCutOff));
    if (tempOuter >= InnerCutOff) {
        tempOuter = InnerCutOff - 0.001f;
    }

    OuterCutOff = tempOuter;
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
