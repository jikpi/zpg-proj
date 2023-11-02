//
// Created by KOP0269 on 25.9.23.
//

#ifndef ZPG_TEST_GLSLSHADER_H
#define ZPG_TEST_GLSLSHADER_H

//Include glew
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>
#include <memory>

#include "glm/ext/matrix_float4x4.hpp" // TODO check if used
#include "../Application/DebugErrorMessages/DebugErrorMessages.h"
#include "ShaderType.h"


class GLSLShader {
private:
    const char *ShaderString;
    ShaderType ThisShaderType;

public:
    explicit GLSLShader(const char *new_shader_string, ShaderType type);
    GLSLShader();
    ~GLSLShader();
    GLSLShader(const GLSLShader &) = delete;
    GLSLShader &operator=(const GLSLShader &) = delete;
    GLSLShader(GLSLShader &&other) noexcept;
    GLSLShader &operator=(GLSLShader &&other) noexcept;

    GLuint Shader;
};


#endif //ZPG_TEST_GLSLSHADER_H
