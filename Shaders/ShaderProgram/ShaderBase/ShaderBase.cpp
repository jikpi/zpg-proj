//
// Created by KOP0269 on 10/27/23.
//

#include <iostream>
#include "ShaderBase.h"
#include "glm/gtc/type_ptr.hpp"

ShaderBase::ShaderBase() : IsVertexShaderAttached(false), IsFragmentShaderAttached(false), IsFinalized(false) {
    ShaderProgramGLuint = glCreateProgram();
}

ShaderBase::~ShaderBase() {
    if (this->IsVertexShaderAttached) {
        glDetachShader(ShaderProgramGLuint, VertexShader->Shader);
    }

    if (this->IsFragmentShaderAttached) {
        glDetachShader(ShaderProgramGLuint, FragmentShader->Shader);
    }

    glDeleteProgram(ShaderProgramGLuint);
    ShaderProgramGLuint = 0;
}

void ShaderBase::FinalizeGLSLattachment() {
    if (!IsFragmentShaderAttached || !IsVertexShaderAttached) {
        std::cerr << "ERROR: SHADERPROGRAM NOT FINALIZED." << std::endl;
        this->PrintName();
        return;
    }
    glLinkProgram(ShaderProgramGLuint);
    this->IsFinalized = true;
}

void ShaderBase::PrintName() const {
    std::cerr << "ShaderProgram name: \"" << this->Name << "\"" << std::endl;
}

void
ShaderBase::AttachShaders(std::unique_ptr<GLSLShader> newVertexShader, std::unique_ptr<GLSLShader> newFragmentShader) {
    this->VertexShader = std::move(newVertexShader);
    this->FragmentShader = std::move(newFragmentShader);

    glAttachShader(ShaderProgramGLuint, this->VertexShader->Shader);
    glAttachShader(ShaderProgramGLuint, this->FragmentShader->Shader);

    this->IsVertexShaderAttached = true;
    this->IsFragmentShaderAttached = true;
}

void ShaderBase::UseProgram() const {
    glUseProgram(ShaderProgramGLuint);
}

void ShaderBase::StopProgram() {
    glUseProgram(0);
}

void ShaderBase::SendToShader(GLint location, const glm::mat4 &matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

}

void ShaderBase::SendToShader(GLint location, const glm::mat3 &matrix) {
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

}

void ShaderBase::SendToShader(GLint location, const glm::vec3 &vector) {
    glUniform3fv(location, 1, glm::value_ptr(vector));

}

void ShaderBase::SendToShader(GLint location, const float &value) {
    glUniform1f(location, value);

}

void ShaderBase::SendToShader(GLint location, const int &value) {
    glUniform1i(location, value);


}

GLint ShaderBase::GetUniformLocation(const char *name) const {
    return glGetUniformLocation(ShaderProgramGLuint, name);
}

ShaderBase::ShaderBase(ShaderBase &&other) noexcept {
    ShaderProgramGLuint = other.ShaderProgramGLuint;
    IsVertexShaderAttached = other.IsVertexShaderAttached;
    IsVertexShaderAttached = other.IsVertexShaderAttached;
    IsFragmentShaderAttached = other.IsFragmentShaderAttached;
    VertexShader = std::move(other.VertexShader);
    FragmentShader = std::move(other.FragmentShader);
    IsFinalized = other.IsFinalized;

    other.ShaderProgramGLuint = 0;
    other.IsVertexShaderAttached = false;
    other.IsFragmentShaderAttached = false;
    other.IsFinalized = false;
}

ShaderBase &ShaderBase::operator=(ShaderBase &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    ShaderProgramGLuint = other.ShaderProgramGLuint;
    IsVertexShaderAttached = other.IsVertexShaderAttached;
    IsVertexShaderAttached = other.IsVertexShaderAttached;
    IsFragmentShaderAttached = other.IsFragmentShaderAttached;
    VertexShader = std::move(other.VertexShader);
    FragmentShader = std::move(other.FragmentShader);
    IsFinalized = other.IsFinalized;

    other.ShaderProgramGLuint = 0;
    other.IsVertexShaderAttached = false;
    other.IsFragmentShaderAttached = false;
    other.IsFinalized = false;

    return *this;
}
