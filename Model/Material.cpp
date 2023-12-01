//
// Created by KOP0269 on 10/26/23.
//

#include "Material.h"
#include "../Application/Configuration/AGlobalConfig.h"

Material::Material(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float specularShineValue)
        : AmbientColor(ambientColor),
          DiffuseColor(diffuseColor),
          SpecularColor(specularColor),
          ShineValue(specularShineValue),
          MaterialTexture(nullptr) {
}

Material::Material() : Material(DEF_MATERIAL_COLOR_AMBIENT,
                                DEF_MATERIAL_COLOR_DIFFUSE,
                                DEF_MATERIAL_COLOR_SPECULAR,
                                DEF_MATERIAL_SHINEVALUE) {
}

Material::Material(glm::vec3 diffuseColor) : Material(DEF_MATERIAL_COLOR_AMBIENT,
                                                      DEF_MATERIAL_COLOR_DIFFUSE,
                                                      DEF_MATERIAL_COLOR_SPECULAR,
                                                      DEF_MATERIAL_SHINEVALUE) {

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
