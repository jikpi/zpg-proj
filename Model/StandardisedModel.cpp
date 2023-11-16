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

StandardisedModel::StandardisedModel(ModelStamp stamp, std::string name)
        : BaseModelData(
        std::move(name),
        stamp) {
    Transformations = std::make_shared<TransfComposite>();
    SelectedShaderProgram = nullptr;

}

std::string StandardisedModel::Info() const {
    return BaseModelData::Name;
}

StandardisedModel &StandardisedModel::InsertTransfMove(glm::vec3 transformation) {
    Transformations->Insert(std::make_shared<Move>(transformation));

    return *this;
}

StandardisedModel &StandardisedModel::InsertTransfRotate(float angle, glm::vec3 transformation) {
    Transformations->Insert(std::make_shared<Rotate>(angle, transformation));

    return *this;
}

StandardisedModel &StandardisedModel::InsertTransfScale(glm::vec3 transformation) {
    Transformations->Insert(std::make_shared<Scale>(transformation));

    return *this;
}

StandardisedModel &StandardisedModel::InsertTransfComposite(const std::shared_ptr<Transformation> &transformation) {
    Transformations->Insert(transformation);

    return *this;
}


void StandardisedModel::SetShaderProgram(ShaderHandler *shaderProgram) {
    SelectedShaderProgram = shaderProgram;
}

ShaderHandler *StandardisedModel::GetShaderProgram() const {
    return SelectedShaderProgram;
}

std::string StandardisedModel::Name() const {
    return BaseModelData::Name;
}

std::string StandardisedModel::Stamp() const {
    std::string stamp;
    if (BaseModelData::Stamp & MODEL_STAMP_VERTICES) {
        stamp += "Vertices ";
    }
    if (BaseModelData::Stamp & MODEL_STAMP_NORMALS) {
        stamp += "Normals ";
    }
    if (BaseModelData::Stamp & MODEL_STAMP_TEXTURE_COORDS) {
        stamp += "Texture Coords ";
    }

    return stamp;
}

StandardisedModel::StandardisedModel(StandardisedModel &&other) noexcept
        : BaseModelData(std::move(other)) { // NOLINT(*-use-after-move)

    Transformations = std::move(other.Transformations);// NOLINT(*-use-after-move)
    SelectedShaderProgram = other.SelectedShaderProgram;
    material = other.material;

    BaseModelData::operator=(std::move(other));
}


StandardisedModel &StandardisedModel::operator=(StandardisedModel &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    Transformations = std::move(other.Transformations);
    SelectedShaderProgram = other.SelectedShaderProgram;
    material = other.material;

    BaseModelData::operator=(std::move(other));
    return *this;
}
