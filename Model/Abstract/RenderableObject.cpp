//
// Created by KOP0269 on 10/27/23.
//

#include <iostream>
#include "RenderableObject.h"

glm::mat4 RenderableObject::GetTransf() const {
    return Transformations->GetResult();
}

void RenderableObject::ConsolidateTransf(glm::mat4 transformation) {
    Transformations->Consolidate(transformation);
    this->HasBeenTransformed = true;

}

void RenderableObject::DoTransf(glm::mat4 transformation) {
    this->Transformations->UseAndRemember(transformation);
    this->HasBeenTransformed = true;
}

void RenderableObject::DoTransf() {
    //Dont call transformations at all if nothing to do, and no transformation is sent.
    if (this->Transformations->TransformationsEmpty()) {
        return;
    }

    this->Transformations->UseAndRemember();
    this->HasBeenTransformed = true;
}

void RenderableObject::SetTransf(glm::mat4 transformation) {
    Transformations->SetResult(transformation);
    this->HasBeenTransformed = true;
}

void RenderableObject::ClearTransf() {
    Transformations->ClearTransformations();
    this->HasBeenTransformed = true;
}

void RenderableObject::ResetTransf() {
    Transformations->ResetResult();
    this->HasBeenTransformed = true;
}

void RenderableObject::SetMaterial(Material newMaterial) {
    if (this->material.GetTexture() != nullptr) {
        newMaterial.SetTexture(this->material.GetTexture());
    }

    this->material = newMaterial;
}

void RenderableObject::SetDefaultMaterial() {
    this->material = Material();
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

glm::mat3 &RenderableObject::GetNormalMatrix() {
    if (HasBeenTransformed) {
        HasBeenTransformed = false;

        this->NormalMatrix = glm::mat3(glm::transpose(glm::inverse(Transformations->GetResult())));

        return this->NormalMatrix;
    }

    return this->NormalMatrix;
}

void RenderableObject::InsertAnimation(std::unique_ptr<AnyAnimation> animation) {
    this->Animations.push_back(std::move(animation));
}

void RenderableObject::ClearAnimations() {
    this->Animations.clear();
}

void RenderableObject::DoAnyAnimation(float t) {
    if (!this->Animations.empty()) {
        for (auto &animation: this->Animations) {
            animation->DoAnimation(t);
        }

        this->AnimationTransformations->ResetResult();
        this->AnimationTransformations->ClearTransformations();

        for (auto &animation: this->Animations) {
            if (animation->Enabled) {
                this->AnimationTransformations->Insert(animation->GetResult());
            }
        }
        this->DoTransf();
    } else {
        this->DoTransf();
    }
}

