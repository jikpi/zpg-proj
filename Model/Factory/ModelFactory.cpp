//
// Created by KOP0269 on 10/6/23.
//

#include "ModelFactory.h"
#include "../../Application/DebugErrorMessages/DebugErrorMessages.h"

#include <utility>
#include <stdexcept>
#include <iostream>

std::shared_ptr<StandardisedModel> ModelFactory::PositionNormal(const float *model, int size, std::string Name) {
    auto newStandModel = std::make_shared<StandardisedModel>(model, size, "PositionNormal", std::move(Name));

    //VBO
    //A named block of memory, that contains positions, normals, colors, ...
    glGenBuffers(1, &newStandModel->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glBufferData(GL_ARRAY_BUFFER, newStandModel->GetModelDataSize() * sizeof(float), newStandModel->GetModelDataRaw(),
                 GL_STATIC_DRAW);
    DebugErrorMessages::PrintGLErrors("VBO");

    //VAO
    //Tells GPU how data is structured in 1 or more VBOs
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
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
    newStandModel->RenderingSize = newStandModel->GetModelDataSize() / 6;
    CheckBadModelSize(newStandModel, 6);
    newStandModel->Initialize();

    newStandModel->DeleteModelData();
    return newStandModel;
}

std::shared_ptr<StandardisedModel> ModelFactory::PositionNormalTex(const float *model, int size, std::string Name) {
    auto newStandModel = std::make_shared<StandardisedModel>(model, size, "PositionNormalTex", std::move(Name));

    //(VBO)
    GLuint VBO = 0;
    glGenBuffers(1, &newStandModel->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glBufferData(GL_ARRAY_BUFFER, newStandModel->GetModelDataSize() * sizeof(float), newStandModel->GetModelDataRaw(),
                 GL_STATIC_DRAW);
    DebugErrorMessages::PrintGLErrors("VBO");

    //vertex attribute object(VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) (3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *) (6 * sizeof(float)));


    //Attach VAO to model
    newStandModel->SetVAO(VAO);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    DebugErrorMessages::PrintGLErrors("VAO");

    //3 for position, 3 for normal, 2 for texture
    newStandModel->RenderingSize = newStandModel->GetModelDataSize() / 8;
    CheckBadModelSize(newStandModel, 8);

    newStandModel->Initialize();

    newStandModel->DeleteModelData();
    return newStandModel;
}

std::shared_ptr<StandardisedModel> ModelFactory::Position(const float *model, int size, std::string Name) {
    auto newStandModel = std::make_shared<StandardisedModel>(model, size, "XYZ", std::move(Name));


    //    vertex buffer object (VBO)
    glGenBuffers(1, &newStandModel->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glBufferData(GL_ARRAY_BUFFER, newStandModel->GetModelDataSize() * sizeof(float), newStandModel->GetModelDataRaw(),
                 GL_STATIC_DRAW);

    DebugErrorMessages::PrintGLErrors("VBO");

    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, newStandModel->VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //Attach VAO to model
    newStandModel->SetVAO(VAO);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    DebugErrorMessages::PrintGLErrors("VAO");


    //3 for position
    newStandModel->RenderingSize = newStandModel->GetModelDataSize() / 3;
    CheckBadModelSize(newStandModel, 3);
    newStandModel->Initialize();

    newStandModel->DeleteModelData();
    return newStandModel;
}

void ModelFactory::CheckBadModelSize(std::shared_ptr<StandardisedModel> &model, int stride) {
    if(model->RenderingSize % stride != 0)
    {
        std::cerr << "Model size is incompatible with selected type, name:" << model->Name() << std::endl;
        std::cerr << "Model size:" << model->GetModelDataSize() << std::endl;
        std::cerr << "Stamp: " << model->Stamp() << std::endl;
        std::cerr << "########################" << std::endl;
    }

    if(model->GetModelDataSize() <= 0 || model->RenderingSize <= 0)
    {
        throw std::runtime_error("Model size is <= 0");
    }
}
