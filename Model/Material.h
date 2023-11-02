//
// Created by KOP0269 on 10/26/23.
//

#ifndef ZPG_TEST_MATERIAL_H
#define ZPG_TEST_MATERIAL_H


#include "glm/vec3.hpp"

class Material {
private:

public:
    Material(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float specularShineValue);
    explicit Material(glm::vec3 diffuseColor);
    Material();
    glm::vec3 AmbientColor{};
    glm::vec3 DiffuseColor{};
    glm::vec3 SpecularColor{};
    float ShineValue;

};


#endif //ZPG_TEST_MATERIAL_H
