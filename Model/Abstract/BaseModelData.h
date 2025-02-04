//
// Created by KOP0269 on 25.9.23.
//

#ifndef ZPG_TEST_BASEMODELDATA_H
#define ZPG_TEST_BASEMODELDATA_H

//Include glew
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <memory>
#include "../ModelStamp.h"


class BaseModelData {
protected:
    GLuint VAO;
    GLuint VBO;
    bool IsInitialized = false;
    ModelStamp Stamp;
    std::string Name;
    int RenderingSize;

public:
    BaseModelData(std::string name, ModelStamp Stamp);
    virtual ~BaseModelData() = default;
    BaseModelData(const BaseModelData &) = delete;
    BaseModelData &operator=(const BaseModelData &) = delete;
    BaseModelData(BaseModelData &&other) noexcept;
    BaseModelData &operator=(BaseModelData &&other) noexcept;
    friend class ModelFactory;


    void Initialize();
    [[nodiscard]] virtual std::string Info() const = 0;
    virtual void BindVertexArray();
    void SetVAO(GLuint vao);
    [[nodiscard]] int GetRenderingSize() const;
};


#endif //ZPG_TEST_BASEMODELDATA_H
