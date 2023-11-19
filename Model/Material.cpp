//
// Created by KOP0269 on 10/26/23.
//

#include "Material.h"

Material::Material(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float specularShineValue)
        : AmbientColor(ambientColor),
          DiffuseColor(diffuseColor),
          SpecularColor(specularColor),
          ShineValue(specularShineValue),
          MaterialTexture(nullptr){
}

Material::Material() : Material(glm::vec3(0.01f, 0.01f, 0.01f),
                                glm::vec3(1.0, 1.0, 1.0),
                                glm::vec3(0.5f, 0.5f, 0.5f),
                                100.0f) {
}

Material::Material(glm::vec3 diffuseColor) : Material(glm::vec3(0.01f, 0.01f, 0.01f),
                                                      diffuseColor,
                                                      glm::vec3(1.0f, 1.0f, 1.0f),
                                                      250.0f) {

}

void Material::SetTexture(Texture *texture) {
    MaterialTexture = texture;
}

Texture *Material::GetTexture() {
    return MaterialTexture;
}

void Material::RemoveTexture() {
    MaterialTexture = nullptr;
}
