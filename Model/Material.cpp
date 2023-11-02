//
// Created by KOP0269 on 10/26/23.
//

#include "Material.h"

Material::Material(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float specularShineValue)
        : AmbientColor(ambientColor),
          DiffuseColor(diffuseColor),
          SpecularColor(specularColor),
          ShineValue(specularShineValue) {
}

Material::Material() : Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                glm::vec3(0.3, 0.3, 1.0),
                                glm::vec3(1.0f, 1.0f, 1.0f),
                                250.0f) {
}

Material::Material(glm::vec3 diffuseColor) : Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                                      diffuseColor,
                                                      glm::vec3(1.0f, 1.0f, 1.0f),
                                                      250.0f) {

}
