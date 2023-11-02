//
// Created by KOP0269 on 10/8/23.
//

#include "Rotate.h"

Rotate::Rotate(float angle, glm::vec3 axis) : angle(angle), axisVector(axis) {}

glm::mat4 Rotate::Use(const glm::mat4 &input) {
    return glm::rotate(input, glm::radians(angle), axisVector);
}