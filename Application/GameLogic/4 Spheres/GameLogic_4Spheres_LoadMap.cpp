//
// Created by lvi on 1.12.23.
//


#include "GameLogic_4Spheres.h"
#include "../../../Shaders/Lighting/LightDirectional.h"

void GameLogic_4Spheres::LoadMap() {
    Resources->CreateNewMap("4 Spheres");
    map = Resources->GetMap("4 Spheres").get();

    ShaderHandler *PhongShader = SelectShader(Resources->Shaders, "Phong");
    ShaderHandler *Skybox = SelectShader(Resources->Shaders, "Skybox");

    std::shared_ptr<StandardisedModel> objectSphere1 = Resources->ModelObjectController.UseAny("sphere.obj",
                                                                                               "Test model 1");
    objectSphere1->SetShaderProgram(PhongShader);
    Resources->AddObjectToMap(map, objectSphere1);

    std::shared_ptr<StandardisedModel> objectSphere2 = Resources->ModelObjectController.UseAny("sphere.obj",
                                                                                               "Test model 2");
    objectSphere2->SetShaderProgram(PhongShader);
    Resources->AddObjectToMap(map, objectSphere2);

    std::shared_ptr<StandardisedModel> objectSphere3 = Resources->ModelObjectController.UseAny("sphere.obj",
                                                                                               "Test model 3");
    objectSphere3->SetShaderProgram(PhongShader);
    Resources->AddObjectToMap(map, objectSphere3);

    std::shared_ptr<StandardisedModel> objectSphere4 = Resources->ModelObjectController.UseAny("sphere.obj",
                                                                                               "Test model 4");
    objectSphere4->SetShaderProgram(PhongShader);
    Resources->AddObjectToMap(map, objectSphere4);

//    std::shared_ptr<LightSpot> spotLight = std::make_shared<LightSpot>(glm::vec3(0.0f, 0.0f, 0.0f),
//                                                                       glm::vec3(0.0f, 1.0f, 0));
//    spotLight->SetOuterCutOff(100.0f);
//    spotLight->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
//    map->InsertLight(spotLight);


    std::shared_ptr<LightPoint> pointLight = std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, 0.0f));
    Resources->AddLightToMap(map, pointLight);

    //Directional light
    std::shared_ptr<LightDirectional> directionalLight = std::make_shared<LightDirectional>(
            glm::vec3(0.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f));
    directionalLight->SetColor(glm::vec3(0.9f, 0.9f, 0.9f));
//    mapManager->AddLightToMap(map, directionalLight);


    ////Objects transformations

    objectSphere1->InsertTransfMove(glm::vec3(1.5f, 0.0f, 1.5f)).ConsolidateTransf();
    objectSphere2->InsertTransfMove(glm::vec3(-1.5f, 0.0f, 1.5f)).ConsolidateTransf();
    objectSphere3->InsertTransfMove(glm::vec3(1.5f, 0.0f, -1.5f)).ConsolidateTransf();
    objectSphere4->InsertTransfMove(glm::vec3(-1.5f, 0.0f, -1.5f)).ConsolidateTransf();



    ////Skybox
    std::shared_ptr<StandardisedModel> pmSkybox = Resources->ModelObjectController.UsePosition("skybox.obj", "Skybox");
    pmSkybox->SetShaderProgram(Skybox);
    Texture *skyboxTexture = Resources->TextureObjectsController.UseCubemap("Lesson/FieldSkybox/field");
    pmSkybox->SetTexture(skyboxTexture);
    Resources->AddSkyboxToMap(map, pmSkybox);
}