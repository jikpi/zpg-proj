//
// Created by KOP0269 on 10/20/23.
//

#include "Light.h"
#include "../../Application/Configuration/AGlobalConfig.h"

Light::Light(const glm::vec3 &position, const glm::vec3 &color, float intensity) : Position(position),
                                                                                   Color(color),
                                                                                   Intensity(intensity),
                                                                                   Constant(DEF_LIGHT_CONSTANT),
                                                                                   Linear(DEF_LIGHT_LINEAR),
                                                                                   Quadratic(DEF_LIGHT_QUADRATIC) {

}

Light::Light(const glm::vec3 &position) : Light(position, DEF_LIGHT_COLOR, DEF_LIGHT_INTENSITY) {
}


void Light::setPosition(const glm::vec3 &newPosition) {
    Light::Position = newPosition;
}

const glm::vec3 &Light::getPosition() const {
    return Position;
}

float Light::getIntensity() const {
    return Intensity;
}

const glm::vec3 &Light::getColor() const {
    return Color;
}

void Light::setColor(const glm::vec3 &newColor) {
    Light::Color = newColor;
}

void Light::setIntensity(float newIntensity) {
    Light::Intensity = newIntensity;
}

void Light::setConstant(float newConstant) {
    Constant = newConstant;
}

void Light::setLinear(float newLinear) {
    Linear = newLinear;
}

void Light::setQuadratic(float newQuadratic) {
    Quadratic = newQuadratic;
}

float Light::getConstant() const {
    return Constant;
}

float Light::getLinear() const {
    return Linear;
}

float Light::getQuadratic() const {
    return Quadratic;
}
