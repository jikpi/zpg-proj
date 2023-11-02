//
// Created by KOP0269 on 10/8/23.
//

#ifndef ZPG_TEST_ROTATE_H
#define ZPG_TEST_ROTATE_H


#include "../Abstract/Transformation.h"

class Rotate : public Transformation {
private:
    float angle;
    glm::vec3 axisVector;

public:
    Rotate(float angle, glm::vec3 axis);

    [[nodiscard]] glm::mat4 Use(const glm::mat4 &input) override;
};


#endif //ZPG_TEST_ROTATE_H
