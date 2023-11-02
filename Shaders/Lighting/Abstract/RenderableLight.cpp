//
// Created by KOP0269 on 11/2/23.
//

#include <stdexcept>
#include <iostream>
#include "RenderableLight.h"
#include "../../../Application/Configuration/AGlobalConfig.h"

RenderableLight::RenderableLight(LightType type, const glm::vec3 &color, float intensity) : Color(color),
                                                                                            Intensity(intensity),
                                                                                            Type(type) {

}

RenderableLight::RenderableLight(LightType type, const glm::vec3 &color) : RenderableLight(type, color,
                                                                                           DEF_LIGHT_INTENSITY) {

}

RenderableLight::RenderableLight(LightType type, float intensity) : RenderableLight(type, DEF_LIGHT_COLOR, intensity) {

}

RenderableLight::RenderableLight(LightType type) : RenderableLight(type, DEF_LIGHT_COLOR, DEF_LIGHT_INTENSITY) {

}

RenderableLight::RenderableLight() {
    Type = LIGHT_TYPE_POINT;
    throw std::runtime_error("RenderableLight: DEBUG: RenderableLight is not implemented");
}

const glm::vec3 &RenderableLight::GetColor() const {
    return Color;
}

float RenderableLight::GetIntensity() const {
    return Intensity;
}

LightType RenderableLight::GetType() const {
    return Type;
}

void RenderableLight::SetColor(const glm::vec3 &newColor) {
    Color = newColor;
}

void RenderableLight::SetIntensity(float newIntensity) {
    Intensity = newIntensity;
}

void RenderableLight::PrintFalseImplementation_LightPoint() {
    std::cerr << "ERROR: RenderableLight: Tried accessing 'LightPoint' members of different type!" << std::endl;
}

void RenderableLight::PrintFalseImplementation_LightDirectional() {
    std::cerr << "ERROR: RenderableLight: Tried accessing 'LightDirectional' members of different type!" << std::endl;
}

void RenderableLight::PrintFalseImplementation_LightSpot() {
    std::cerr << "ERROR: RenderableLight: Tried accessing 'LightSpot' members of different type!" << std::endl;
}

void RenderableLight::SetPosition(const glm::vec3 &newPosition) {
    PrintFalseImplementation_LightPoint();
}

const glm::vec3 &RenderableLight::GetPosition() const {
    PrintFalseImplementation_LightPoint();
    throw std::runtime_error("FATAL: RenderableLight: Cannot recover from this error.");
}

void RenderableLight::SetConstant(float newConstant) {
    PrintFalseImplementation_LightPoint();
}

float RenderableLight::GetConstant() const {
    PrintFalseImplementation_LightPoint();
    return 0;
}

void RenderableLight::SetLinear(float newLinear) {
    PrintFalseImplementation_LightPoint();
}

float RenderableLight::GetLinear() const {
    PrintFalseImplementation_LightPoint();
    return 0;
}

void RenderableLight::SetQuadratic(float newQuadratic) {
    PrintFalseImplementation_LightPoint();
}

float RenderableLight::GetQuadratic() const {
    PrintFalseImplementation_LightPoint();
    return 0;
}

void RenderableLight::SetDirection(const glm::vec3 &newDirection) {
    PrintFalseImplementation_LightDirectional();
}

const glm::vec3 &RenderableLight::GetDirection() const {
    PrintFalseImplementation_LightDirectional();
    throw std::runtime_error("FATAL: RenderableLight: Cannot recover from this error.");
}
