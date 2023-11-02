//
// Created by KOP0269 on 11/2/23.
//

#include "LightDirectional.h"
#include "../../Application/Configuration/AGlobalConfig.h"

LightDirectional::LightDirectional(const glm::vec3 &direction, const glm::vec3 &color, float intensity)
        : RenderableLight(LIGHT_TYPE_DIRECTIONAL, color, intensity),
          Direction(direction) {

}

LightDirectional::LightDirectional(const glm::vec3 &direction, const glm::vec3 &color)
        : RenderableLight(LIGHT_TYPE_DIRECTIONAL, color),
          Direction(direction) {

}

LightDirectional::LightDirectional(const glm::vec3 &direction) : RenderableLight(LIGHT_TYPE_DIRECTIONAL),
                                                                 Direction(direction) {

}

LightDirectional::LightDirectional() : RenderableLight(LIGHT_TYPE_DIRECTIONAL),
                                       Direction(DEF_LIGHT_DIRECTIONAL_DIRECTION) {

}

const glm::vec3 &LightDirectional::GetDirection() const {
    return Direction;
}

void LightDirectional::SetDirection(const glm::vec3 &newDirection) {
    Direction = newDirection;
}
