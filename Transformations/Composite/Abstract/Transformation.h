//
// Created by KOP0269 on 10/8/23.
//

#ifndef ZPG_TEST_TRANSFORMATION_H
#define ZPG_TEST_TRANSFORMATION_H

//Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


class Transformation {
public:
    virtual ~Transformation() = default;
    [[nodiscard]] virtual glm::mat4 Use(const glm::mat4 &input) = 0;
};


#endif //ZPG_TEST_TRANSFORMATION_H
