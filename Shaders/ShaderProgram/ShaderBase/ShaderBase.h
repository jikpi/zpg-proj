//
// Created by KOP0269 on 10/27/23.
//

#ifndef ZPG_TEST_SHADERBASE_H
#define ZPG_TEST_SHADERBASE_H


#include <memory>
#include "../../GLSLShader.h"

class ShaderBase {
private:

protected:
    GLuint ShaderProgramGLuint; //TODO move back to priv

    virtual void PrintName() const;

    bool IsVertexShaderAttached;
    bool IsFragmentShaderAttached;
    bool IsFinalized;

    std::unique_ptr<GLSLShader> VertexShader;
    std::unique_ptr<GLSLShader> FragmentShader;

    static void SendToShader(GLint location, const glm::mat4 &matrix);
    static void SendToShader(GLint location, const glm::mat3 &matrix);
    static void SendToShader(GLint location, const glm::vec3 &vector);
    static void SendToShader(GLint location, const float &value);
    static void SendToShader(GLint location, const int &value);

    GLint GetUniformLocation(const char *name) const;

public:
    ShaderBase();
    ~ShaderBase();
    ShaderBase(const ShaderBase &other) = delete;
    ShaderBase &operator=(const ShaderBase &other) = delete;
    ShaderBase(ShaderBase &&other) noexcept;
    ShaderBase &operator=(ShaderBase &&other) noexcept;

    void
    AttachShaders(std::unique_ptr<GLSLShader> newVertexShader, std::unique_ptr<GLSLShader> newFragmentShader);
    void FinalizeGLSLattachment();

    std::string Name;

    void UseProgram() const;
    static void StopProgram();

};


#endif //ZPG_TEST_SHADERBASE_H
