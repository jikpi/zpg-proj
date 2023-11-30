//
// Created by KOP0269 on 10/8/23.
//

#include "TransfComposite.h"

void TransfComposite::Insert(const std::shared_ptr<Transformation> &transformation) {
    Transformations.push_back(transformation);
}

glm::mat4 TransfComposite::Use(const glm::mat4 &input) {
    glm::mat4 result = input;
    for (const auto &transform: Transformations) {
        result = transform->Use(result);
    }

    Result = result;
    return ReturnWithAdditiveTransformation(result);
}

glm::mat4 TransfComposite::Use() {
    return this->Use(glm::mat4(1.0f));
}

void TransfComposite::SingleUse(const std::shared_ptr<Transformation> &transformation) {
    glm::mat4 result = transformation->Use(glm::mat4(1.0f));
    Result = result;
}

glm::mat4 TransfComposite::MasterUseAndRemember(const glm::mat4 &input, bool isIdentity) {
    if (Transformations.empty()) {
        return ReturnWithAdditiveTransformation(input);
    }

    glm::mat4 result;

    if (isIdentity) {
        result = Result;
    } else {
        result = Result * input;
    }

    for (const auto &transform: Transformations) {
        result = transform->Use(result);
    }

    Result = result;
    return ReturnWithAdditiveTransformation(result);
}

glm::mat4 TransfComposite::UseAndRemember(const glm::mat4 &input) {
    return this->MasterUseAndRemember(input, false);
}

glm::mat4 TransfComposite::UseAndRemember() {
    return this->MasterUseAndRemember(glm::mat4(), true);
}

void TransfComposite::ClearTransformations() {
    Transformations.clear();
}

void TransfComposite::ResetResult() {
    Result = glm::mat4(1.0f);
}

glm::mat4 TransfComposite::Consolidate(const glm::mat4 &input) {
    glm::mat4 result;
    if (Transformations.empty()) {
        return ReturnWithAdditiveTransformation(input);
    } else {
        result = this->UseAndRemember(input);
        this->ClearTransformations();
        Result = result;
        return result;
    }
}

glm::mat4 TransfComposite::Consolidate() {
    return this->Consolidate(glm::mat4(1.0f));
}

glm::mat4 TransfComposite::GetResult() {
    return ReturnWithAdditiveTransformation(Result);
}

void TransfComposite::SetResult(glm::mat4 result) {
    Result = result;
}

bool TransfComposite::TransformationsEmpty() const {
    return Transformations.empty();
}

void TransfComposite::SetAdditiveTransformation(const std::shared_ptr<Transformation> &additiveTransformation) {
    this->AdditiveTransformation = additiveTransformation.get();
}

void TransfComposite::ClearAdditiveTransformation() {
    this->AdditiveTransformation = nullptr;
}

Transformation * TransfComposite::GetAdditiveTransformation() const {
    return this->AdditiveTransformation;
}

glm::mat4 TransfComposite::ReturnWithAdditiveTransformation(const glm::mat4 &input) {
    if (this->AdditiveTransformation == nullptr) {
        return input;
    }

    glm::mat4 result = this->AdditiveTransformation->Use(glm::mat4(1.0f));
    return result * input;
}

