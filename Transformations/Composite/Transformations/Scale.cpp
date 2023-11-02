//
// Created by KOP0269 on 10/8/23.
//

#include "Scale.h"

Scale::Scale(glm::vec3 scale) : scaleVector(scale) {}

glm::mat4 Scale::Use(const glm::mat4 &input) {
    return glm::scale(input, scaleVector);
}
