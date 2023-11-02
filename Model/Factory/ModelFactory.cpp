//
// Created by KOP0269 on 10/6/23.
//

#include "ModelFactory.h"
#include "../../Application/DebugErrorMessages/DebugErrorMessages.h"

#include <utility>

std::shared_ptr<StandardisedModel> ModelFactory::PositionNormal(const float *model, int size, std::string Name) {
    auto model1 = std::make_shared<StandardisedModel>(model, size, "PositionNormal", std::move(Name));

    //VBO
    //A named block of memory, that contains positions, normals, colors, ...
    glGenBuffers(1, &model1->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, model1->VBO);
    glBufferData(GL_ARRAY_BUFFER, model1->GetModelDataSize() * sizeof(float), model1->GetModelDataRaw(),
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
    model1->SetVAO(VAO);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    DebugErrorMessages::PrintGLErrors("VAO");

    //3 for position, 3 for normal
    model1->RenderingSize = model1->GetModelDataSize() / 6;
    model1->Initialize();

    model1->DeleteModelData();
    return model1;
}

std::shared_ptr<StandardisedModel> ModelFactory::XYZ_Model(const float *model, int size, std::string Name) {
    auto model1 = std::make_shared<StandardisedModel>(model, size, "XYZ", std::move(Name));


    //    vertex buffer object (VBO)
    glGenBuffers(1, &model1->VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, model1->VBO);
    glBufferData(GL_ARRAY_BUFFER, model1->GetModelDataSize() * sizeof(float), model1->GetModelDataRaw(),
                 GL_STATIC_DRAW);

    DebugErrorMessages::PrintGLErrors("VBO");

    //Vertex Array Object (VAO)
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, model1->VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    //Attach VAO to model
    model1->SetVAO(VAO);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    DebugErrorMessages::PrintGLErrors("VAO");


    //3 for position
    model1->RenderingSize = model1->GetModelDataSize() / 3;
    model1->Initialize();

    model1->DeleteModelData();
    return model1;
}
