//
// Created by KOP0269 on 10/8/23.
//

#ifndef ZPG_TEST_SCALE_H
#define ZPG_TEST_SCALE_H


#include "../Abstract/Transformation.h"

class Scale : public Transformation {
private:
    glm::vec3 scaleVector;

public:
    explicit Scale(glm::vec3 scale);

    [[nodiscard]] glm::mat4 Use(const glm::mat4 &input) override;
};


#endif //ZPG_TEST_SCALE_H
