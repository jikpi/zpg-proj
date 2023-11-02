//
// Created by KOP0269 on 11/2/23.
//

#include "LightDirectional.h"
#include "../../Application/Configuration/AGlobalConfig.h"
#include "glm/geometric.hpp"

LightDirectional::LightDirectional(const glm::vec3 &direction, const glm::vec3 &color, float intensity)
        : RenderableLight(LIGHT_TYPE_DIRECTIONAL, color, intensity),
          Direction(glm::normalize(direction)) {

}

LightDirectional::LightDirectional(const glm::vec3 &direction, const glm::vec3 &color) :
        LightDirectional(direction,
                         color,
                         DEF_LIGHT_INTENSITY) {

}

LightDirectional::LightDirectional(const glm::vec3 &direction) :
        LightDirectional(direction, DEF_LIGHT_COLOR,
                         DEF_LIGHT_INTENSITY) {

}

LightDirectional::LightDirectional() : LightDirectional(DEF_LIGHT_DIRECTIONAL_DIRECTION,
                                                        DEF_LIGHT_COLOR,
                                                        DEF_LIGHT_INTENSITY) {

}

const glm::vec3 &LightDirectional::GetDirection() const {
    return Direction;
}

void LightDirectional::SetDirection(const glm::vec3 &newDirection) {
    Direction = newDirection;
}
