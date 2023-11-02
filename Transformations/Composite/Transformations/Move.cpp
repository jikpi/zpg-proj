//
// Created by KOP0269 on 10/8/23.
//

#include "Move.h"

Move::Move(glm::vec3 move) : moveVector(move) {

}

glm::mat4 Move::Use(const glm::mat4 &input) {
    return glm::translate(input, moveVector);
}
