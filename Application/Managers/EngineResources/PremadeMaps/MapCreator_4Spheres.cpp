//
// Created by lvi on 11/18/23.
//

#include "MapCreator.h"
#include "../../../../Shaders/Lighting/LightSpot.h"
#include "../../../../Model/Factory/ModelFactory.h"
#include "../../../../Model/Animation/BezierAnimation.h"
#include "../../../../Shaders/Lighting/LightDirectional.h"

void
MapCreator::FourSpheres(const std::string &mapName, std::vector<std::shared_ptr<ShaderHandler>> &shaders, ResourcesManager *mapManager) {

    mapManager->CreateNewMap(mapName);
    std::shared_ptr<Map> &map = mapManager->GetMap(mapName);

    ShaderHandler *PhongShader = SelectShader(shaders, "Phong");
    ShaderHandler *Skybox = SelectShader(shaders, "Skybox");

    std::shared_ptr<StandardisedModel> objectSphere1 = mapManager->ModelObjectController.UseAny("sphere.obj",
                                                                                               "Test model 1");
    objectSphere1->SetShaderProgram(PhongShader);
    mapManager->AddObjectToMap(map, objectSphere1);

    std::shared_ptr<StandardisedModel> objectSphere2 = mapManager->ModelObjectController.UseAny("sphere.obj",
                                                                                               "Test model 2");
    objectSphere2->SetShaderProgram(PhongShader);
    mapManager->AddObjectToMap(map, objectSphere2);

    std::shared_ptr<StandardisedModel> objectSphere3 = mapManager->ModelObjectController.UseAny("sphere.obj",
                                                                                               "Test model 3");
    objectSphere3->SetShaderProgram(PhongShader);
    mapManager->AddObjectToMap(map, objectSphere3);

    std::shared_ptr<StandardisedModel> objectSphere4 = mapManager->ModelObjectController.UseAny("sphere.obj",
                                                                                               "Test model 4");
    objectSphere4->SetShaderProgram(PhongShader);
    mapManager->AddObjectToMap(map, objectSphere4);

//    std::shared_ptr<LightSpot> spotLight = std::make_shared<LightSpot>(glm::vec3(0.0f, 0.0f, 0.0f),
//                                                                       glm::vec3(0.0f, 1.0f, 0));
//    spotLight->SetOuterCutOff(100.0f);
//    spotLight->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
//    map->InsertLight(spotLight);


    std::shared_ptr<LightPoint> pointLight = std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, 0.0f));
    map->InsertLight(pointLight);

    //Directional light
    std::shared_ptr<LightDirectional> directionalLight = std::make_shared<LightDirectional>(
            glm::vec3(0.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f));
    directionalLight->SetColor(glm::vec3(0.9f, 0.9f, 0.9f));
//    mapManager->AddLightToMap(map, directionalLight);


    ////Objects transformations

//    objectSphere1->InsertTransfMove(glm::vec3(-2.0f, 0.0f, 0.0f)).
//            InsertTransfRotate(90, glm::vec3(-1.0f, 0, 0)).ConsolidateTransf();
//    std::unique_ptr<AnyAnimation> animation1 = std::make_unique<BezierAnimation>(0.001f);
//    auto *bezierAnim = dynamic_cast<BezierAnimation *>(animation1.get());
//    ////Bezier points
//    std::vector<glm::vec3> controlPoints = {
//            glm::vec3(0, 0, 0),     // First segment
//            glm::vec3(2, 2, 0),
//            glm::vec3(-4, 4, 0),
//            glm::vec3(6, 0, 0),     // Second segment
////            glm::vec3(8, -10, 0),
////            glm::vec3(10, 4, 0),
////            glm::vec3(12, 0, 0),    // Third segment
////            glm::vec3(14, 20, 20),
////            glm::vec3(16, 25, 15),
////            glm::vec3(18, 15, 10),
////            glm::vec3(20, 10, 5)
//    };
//    for (const auto &point: controlPoints) {
//        bezierAnim->AddPoint(point);
//    }
//    bezierAnim->SetStyle(BezierAnimation::BezierAnimationStyle::RoundAround);
//    objectSphere1->InsertAnimation(std::move(animation1));
//    objectSphere1->InsertTransfRotate(1, glm::vec3(0.0f, 1, 0));

    objectSphere1->InsertTransfMove(glm::vec3(1.5f, 0.0f, 1.5f)).ConsolidateTransf();
    objectSphere2->InsertTransfMove(glm::vec3(-1.5f, 0.0f, 1.5f)).ConsolidateTransf();
    objectSphere3->InsertTransfMove(glm::vec3(1.5f, 0.0f, -1.5f)).ConsolidateTransf();
    objectSphere4->InsertTransfMove(glm::vec3(-1.5f, 0.0f, -1.5f)).ConsolidateTransf();



    ////Skybox
    std::shared_ptr<StandardisedModel> pmSkybox = mapManager->ModelObjectController.UsePosition("skybox.obj", "Skybox");
    pmSkybox->SetShaderProgram(Skybox);
    Texture *skyboxTexture = mapManager->TextureObjectsController.UseCubemap("Lesson/FieldSkybox/field");
    pmSkybox->SetTexture(skyboxTexture);
    map->SetSkybox(pmSkybox);
}
