//
// Created by KOP0269 on 10/6/23.
//

#include "ModelFactory.h"

#include <utility>
#include <stdexcept>

std::shared_ptr<StandardisedModel> ModelFactory::PositionNormal(const float *model, int size, std::string Name) {
    auto newStandModel = std::make_shared<StandardisedModel>(
            static_cast<ModelStamp>(ModelStamp::MODEL_STAMP_VERTICES | MODEL_STAMP_NORMALS), std::move(Name));

    //VBO
    //A named block of memory, that contains positions, normals, colors, ...
    glGenBuffers(1, &newStandModel->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), model,
                 GL_STATIC_DRAW);
    DebugErrorMessages::PrintGLErrors("VBO");

    //VAO
    //Tells GPU how data is structured in 1 or more VBOs
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    //Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Attach VAO to model
    newStandModel->SetVAO(VAO);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    DebugErrorMessages::PrintGLErrors("VAO");

    //3 for position, 3 for normal
    newStandModel->RenderingSize = size / 6;
    newStandModel->Initialize();

    return newStandModel;
}

std::shared_ptr<StandardisedModel> ModelFactory::PositionNormalTex(const float *model, int size, std::string Name) {
    auto newStandModel = std::make_shared<StandardisedModel>(static_cast<ModelStamp>(ModelStamp::MODEL_STAMP_VERTICES | MODEL_STAMP_NORMALS | ModelStamp::MODEL_STAMP_TEXTURE_COORDS), std::move(Name));

    //(VBO)
    glGenBuffers(1, &newStandModel->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), model,
                 GL_STATIC_DRAW);
    DebugErrorMessages::PrintGLErrors("VBO");

    //vertex attribute object(VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) (6 * sizeof(float)));


    //Attach VAO to model
    newStandModel->SetVAO(VAO);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    DebugErrorMessages::PrintGLErrors("VAO");

    //3 for position, 3 for normal, 2 for texture
    newStandModel->RenderingSize = size / 8;

    newStandModel->Initialize();

    return newStandModel;
}

std::shared_ptr<StandardisedModel> ModelFactory::Position(const float *model, int size, std::string Name) {
    auto newStandModel = std::make_shared<StandardisedModel>(static_cast<ModelStamp>(ModelStamp::MODEL_STAMP_VERTICES), std::move(Name));


    //    vertex buffer object (VBO)
    glGenBuffers(1, &newStandModel->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), model,
                 GL_STATIC_DRAW);

    DebugErrorMessages::PrintGLErrors("VBO");

    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //Attach VAO to model
    newStandModel->SetVAO(VAO);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    DebugErrorMessages::PrintGLErrors("VAO");


    //3 for position
    newStandModel->RenderingSize = size / 3;
    newStandModel->Initialize();

    return newStandModel;
}

std::shared_ptr<StandardisedModel> ModelFactory::AssimpPositionNormalTex(std::vector<float> &model, std::string Name) {
    auto newStandModel = std::make_shared<StandardisedModel>(static_cast<ModelStamp>(ModelStamp::MODEL_STAMP_VERTICES | MODEL_STAMP_NORMALS | MODEL_STAMP_TEXTURE_COORDS), std::move(Name));

    float *modelData = model.data();
    auto size = static_cast<GLsizeiptr>(model.size() * sizeof(float));

    //(VBO)
    glGenBuffers(1, &newStandModel->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glBufferData(GL_ARRAY_BUFFER, size, modelData,
                 GL_STATIC_DRAW);
    DebugErrorMessages::PrintGLErrors("VBO");

    //vertex attribute object(VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) (6 * sizeof(float)));


    //Attach VAO to model
    newStandModel->SetVAO(VAO);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    DebugErrorMessages::PrintGLErrors("VAO");

    //3 for position, 3 for normal, 2 for texture
    newStandModel->RenderingSize = static_cast<int>(model.size() / 8);

    newStandModel->Initialize();

    return newStandModel;
}

std::shared_ptr<StandardisedModel> ModelFactory::AssimpPositionNormal(std::vector<float> &model, std::string Name) {
    auto newStandModel = std::make_shared<StandardisedModel>(static_cast<ModelStamp>(ModelStamp::MODEL_STAMP_VERTICES | MODEL_STAMP_NORMALS), std::move(Name));

    float *modelData = model.data();
    auto size = static_cast<GLsizeiptr>(model.size() * sizeof(float));

    //VBO
    //A named block of memory, that contains positions, normals, colors, ...
    glGenBuffers(1, &newStandModel->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glBufferData(GL_ARRAY_BUFFER, size, modelData,
                 GL_STATIC_DRAW);
    DebugErrorMessages::PrintGLErrors("VBO");

    //VAO
    //Tells GPU how data is structured in 1 or more VBOs
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);
    //Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Attach VAO to model
    newStandModel->SetVAO(VAO);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    DebugErrorMessages::PrintGLErrors("VAO");

    //3 for position, 3 for normal
    newStandModel->RenderingSize = static_cast<int>(model.size() / 6);
    newStandModel->Initialize();

    return newStandModel;
}

std::shared_ptr<StandardisedModel> ModelFactory::AssimpPosition(std::vector<float> &model, std::string Name) {
    auto newStandModel = std::make_shared<StandardisedModel>(static_cast<ModelStamp>(ModelStamp::MODEL_STAMP_VERTICES), std::move(Name));

    float *modelData = model.data();
    auto size = static_cast<GLsizeiptr>(model.size() * sizeof(float));


    //    vertex buffer object (VBO)
    glGenBuffers(1, &newStandModel->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glBufferData(GL_ARRAY_BUFFER, size, modelData,
                 GL_STATIC_DRAW);

    DebugErrorMessages::PrintGLErrors("VBO");

    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //Attach VAO to model
    newStandModel->SetVAO(VAO);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    DebugErrorMessages::PrintGLErrors("VAO");


    //3 for position
    newStandModel->RenderingSize = static_cast<int>(model.size() / 3);
    newStandModel->Initialize();

    return newStandModel;
}
