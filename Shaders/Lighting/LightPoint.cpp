//
// Created by KOP0269 on 10/20/23.
//

#include "LightPoint.h"
#include "../../Application/Configuration/AGlobalConfig.h"

LightPoint::LightPoint(const glm::vec3 &position, const glm::vec3 &color, float intensity, float constant,
                       float linear, float quadratic)
        : RenderableLight(LIGHT_TYPE_POINT, color, intensity),
          Position(position),
          Constant(constant),
          Linear(linear),
          Quadratic(quadratic) {

}

LightPoint::LightPoint(const glm::vec3 &position, const glm::vec3 &color) : RenderableLight(LIGHT_TYPE_POINT, color),
                                                                            Position(position),
                                                                            Constant(DEF_LIGHT_CONSTANT),
                                                                            Linear(DEF_LIGHT_LINEAR),
                                                                            Quadratic(DEF_LIGHT_QUADRATIC) {

}

LightPoint::LightPoint(const glm::vec3 &position) : RenderableLight(LIGHT_TYPE_POINT),
                                                    Position(position),
                                                    Constant(DEF_LIGHT_CONSTANT),
                                                    Linear(DEF_LIGHT_LINEAR),
                                                    Quadratic(DEF_LIGHT_QUADRATIC) {

}


void LightPoint::SetPosition(const glm::vec3 &newPosition) {
    LightPoint::Position = newPosition;
}

const glm::vec3 &LightPoint::GetPosition() const {
    return Position;
}

void LightPoint::SetConstant(float newConstant) {
    Constant = newConstant;
}

void LightPoint::SetLinear(float newLinear) {
    Linear = newLinear;
}

void LightPoint::SetQuadratic(float newQuadratic) {
    Quadratic = newQuadratic;
}

float LightPoint::GetConstant() const {
    return Constant;
}

float LightPoint::GetLinear() const {
    return Linear;
}

float LightPoint::GetQuadratic() const {
    return Quadratic;
}
