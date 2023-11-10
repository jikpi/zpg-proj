//
// Created by KOP0269 on 10/27/23.
//

#include "RenderableObject.h"

glm::mat4 RenderableObject::GetTransf() const {
    return Transformations->GetResult();
}

void RenderableObject::ConsolidateTransf(glm::mat4 transformation) const {
    Transformations->Consolidate(transformation);
}

void RenderableObject::DoTransf(glm::mat4 transformation) const {
    this->Transformations->UseAndRemember(transformation);
}

void RenderableObject::SetTransf(glm::mat4 transformation) const {
    Transformations->SetResult(transformation);
}

void RenderableObject::ClearTransf() const {
    Transformations->ClearTransformations();
}

void RenderableObject::ResetTransf() const {
    Transformations->ResetResult();
}

void RenderableObject::SetMaterial(Material newMaterial) {
    if (this->material.GetTexture() != nullptr) {
        newMaterial.SetTexture(this->material.GetTexture());
    }

    this->material = newMaterial;
}

Material RenderableObject::GetMaterial() const {
    return this->material;
}

Texture *RenderableObject::GetTexture() {
    return material.GetTexture();
}

void RenderableObject::SetTexture(Texture *texture) {
    material.SetTexture(texture);
}

