//
// Created by KOP0269 on 10/26/23.
//

#ifndef ZPG_TEST_MATERIAL_H
#define ZPG_TEST_MATERIAL_H


#include "glm/vec3.hpp"
#include "Texture/Texture.h"

class Material {
private:
    Texture* MaterialTexture;

public:
    Material(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float specularShineValue);
    explicit Material(glm::vec3 diffuseColor);
    Material();

    void SetTexture(Texture* texture);
    Texture* GetTexture();

    glm::vec3 AmbientColor{};
    glm::vec3 DiffuseColor{};
    glm::vec3 SpecularColor{};
    float ShineValue;

};


#endif //ZPG_TEST_MATERIAL_H
