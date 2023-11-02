//
// Created by KOP0269 on 25.9.23.
//

#include <stdexcept>
#include "BaseModelData.h"

BaseModelData::BaseModelData(const float *modelData, int modelDataSize, std::string name, std::string Stamp) : VAO(0), VBO(0),
                                                                                                               Name(std::move(name)),
                                                                                                               Stamp(std::move(Stamp)),
                                                                                                               RenderingSize(0) {

    ModelData = std::vector<float>(modelData, modelData + modelDataSize);

}

void BaseModelData::BindVertexArray() {
    //bind VAO
    glBindVertexArray(this->VAO);

}

void BaseModelData::Initialize() {
    if (this->VAO == 0) {
        throw std::runtime_error("VAO uninitialized");
    }

    if (this->VBO == 0) {
        throw std::runtime_error("VBO uninitialized");
    }

    if (this->RenderingSize == 0) {
        throw std::runtime_error("Rendering size uninitialized");
    }

    IsInitialized = true;
}

float *BaseModelData::GetModelDataRaw() {
    return ModelData.data();
}

unsigned long BaseModelData::GetModelDataSize() const {
    return ModelData.size();
}

void BaseModelData::SetVAO(GLuint vao) {
    this->VAO = vao;
}

BaseModelData::BaseModelData(BaseModelData &&other) noexcept {
    VAO = other.VAO;
    VBO = other.VBO;
    ModelData = std::move(other.ModelData);
    IsInitialized = other.IsInitialized;
    Name = other.Name;
    Stamp = other.Stamp;
    RenderingSize = other.RenderingSize;

    other.VAO = 0;
    other.VBO = 0;
    other.IsInitialized = false;
}

BaseModelData &BaseModelData::operator=(BaseModelData &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    VAO = other.VAO;
    VBO = other.VBO;
    ModelData = std::move(other.ModelData);
    IsInitialized = other.IsInitialized;
    Name = other.Name;
    Stamp = other.Stamp;
    RenderingSize = other.RenderingSize;

    other.VAO = 0;
    other.VBO = 0;
    other.IsInitialized = false;
    return *this;
}

int BaseModelData::GetRenderingSize() const {
    return RenderingSize;
}

void BaseModelData::DeleteModelData() {
    this->ModelData.clear();
    this->ModelData.shrink_to_fit();
}
