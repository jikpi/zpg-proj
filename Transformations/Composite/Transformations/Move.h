//
// Created by KOP0269 on 10/8/23.
//

#ifndef ZPG_TEST_MOVE_H
#define ZPG_TEST_MOVE_H


#include "../Abstract/Transformation.h"

class Move : public Transformation {
private:

    glm::vec3 moveVector;

public:
    explicit Move(glm::vec3 move);

    glm::mat4 Use(const glm::mat4 &input) override;
};


#endif //ZPG_TEST_MOVE_H
