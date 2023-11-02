//
// Created by KOP0269 on 10/6/23.
//

#include "StandardisedModel.h"
#include "../Transformations/Composite/Transformations/Move.h"
#include "../Transformations/Composite/Transformations/Rotate.h"
#include "../Transformations/Composite/Transformations/Scale.h"

#include <utility>

StandardisedModel::~StandardisedModel() {
    if (this->VBO != 0) {
        glDeleteBuffers(1, &this->VBO);
        this->VBO = 0;
    }

    if (this->VAO != 0) {
        glDeleteVertexArrays(1, &this->VAO);
        this->VAO = 0;
    }
}

StandardisedModel::StandardisedModel(const float *modelData, int modelDataSize, std::string stamp, std::string name)
        : BaseModelData(modelData,
                        modelDataSize,
                        std::move(name),
                        std::move(stamp)) {
    Transformations = std::make_shared<TransfComposite>();

}

std::string StandardisedModel::Info() const {
    return BaseModelData::Name;
}

StandardisedModel & StandardisedModel::InsertTransfMove(glm::vec3 transformation) {
    Transformations->Insert(std::make_shared<Move>(transformation));

    return *this;
}

StandardisedModel & StandardisedModel::InsertTransfRotate(float angle, glm::vec3 transformation) {
    Transformations->Insert(std::make_shared<Rotate>(angle, transformation));

    return *this;
}

StandardisedModel & StandardisedModel::InsertTransfScale(glm::vec3 transformation) {
    Transformations->Insert(std::make_shared<Scale>(transformation));

    return *this;
}

StandardisedModel & StandardisedModel::InsertTransfComposite(const std::shared_ptr<Transformation> &transformation) {
    Transformations->Insert(transformation);

    return *this;
}

void StandardisedModel::ConsolidateTransf(glm::mat4 transformation) const {
    Transformations->Consolidate(transformation);
}

void StandardisedModel::DoTransf(glm::mat4 transformation) const {
    this->Transformations->UseAndRemember(transformation);
}

glm::mat4 StandardisedModel::GetTransf() const {
    return Transformations->GetResult();
}

void StandardisedModel::SetTransf(glm::mat4 transformation) const {
    Transformations->SetResult(transformation);
}

void StandardisedModel::SetShaderProgram(std::shared_ptr<ShaderHandler> &shaderProgram) {
    SelectedShaderProgram = shaderProgram;
}

const std::weak_ptr<ShaderHandler> &StandardisedModel::GetShaderProgram() const {
    return SelectedShaderProgram;
}

std::string StandardisedModel::Name() const {
    return BaseModelData::Name;
}

std::string StandardisedModel::Stamp() const {
    return BaseModelData::Stamp;
}

StandardisedModel::StandardisedModel(StandardisedModel &&other) noexcept
        : BaseModelData(std::move(other)),
          Transformations(std::move(other.Transformations)), // NOLINT(*-use-after-move)
          SelectedShaderProgram(std::move(other.SelectedShaderProgram)) { // NOLINT(*-use-after-move)
    material = other.material; // NOLINT(*-use-after-move)
}


StandardisedModel &StandardisedModel::operator=(StandardisedModel &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    Transformations = std::move(other.Transformations);
    SelectedShaderProgram = std::move(other.SelectedShaderProgram);
    material = other.material;

    BaseModelData::operator=(std::move(other));
    return *this;
}

void StandardisedModel::SetMaterial(Material newMaterial) {
    this->material = newMaterial;
}

Material StandardisedModel::GetMaterial() const {
    return this->material;
}

void StandardisedModel::ClearTransf() const {
    Transformations->ClearTransformations();
}

void StandardisedModel::ResetTransf() const {
    Transformations->ResetResult();
}

