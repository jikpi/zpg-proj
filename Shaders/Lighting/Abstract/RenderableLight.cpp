//
// Created by KOP0269 on 11/2/23.
//

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