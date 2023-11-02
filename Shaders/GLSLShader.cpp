//
// Created by KOP0269 on 25.9.23.
//
#include <string>
#include <stdexcept>

#include "GLSLShader.h"
#include "ShadersCode/LegacyShaderStrings/LegacyShadersStrings.h"
#include "ShadersCode/Loader/ShaderFileLoader.h"

GLSLShader::GLSLShader(const char *new_shader_string, ShaderType type) : ShaderString(new_shader_string),
                                                                         ThisShaderType(type) {

    switch (type) {
        case VERTEX_SHADER:
            Shader = glCreateShader(GL_VERTEX_SHADER);
            break;
        case FRAGMENT_SHADER:
            Shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            throw std::runtime_error("GLSLShader: Unknown shader type");
    }

    ThisShaderType = type;

    DebugErrorMessages::PrintGLErrors("Shader creation");
    glShaderSource(Shader, 1, &ShaderString, nullptr);
    DebugErrorMessages::PrintGLErrors("Shader source");
    glCompileShader(Shader);
    DebugErrorMessages::PrintGLErrors("Shader compile");
}

GLSLShader::GLSLShader() : GLSLShader(ShaderFileLoader::HardLoadMVPNCleanVertex().c_str(), VERTEX_SHADER) {
}

GLSLShader::~GLSLShader() {
    if (Shader != 0) {
        glDeleteShader(Shader);
        Shader = 0;
    }
}

GLSLShader::GLSLShader(GLSLShader &&other) noexcept {
    ShaderString = other.ShaderString;
    Shader = other.Shader;
    ThisShaderType = other.ThisShaderType;

    other.Shader = 0;
}

GLSLShader &GLSLShader::operator=(GLSLShader &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    ShaderString = other.ShaderString;
    Shader = other.Shader;
    ThisShaderType = other.ThisShaderType;

    other.Shader = 0;
    return *this;
}
