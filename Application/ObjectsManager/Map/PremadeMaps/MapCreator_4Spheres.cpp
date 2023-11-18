//
// Created by lvi on 11/18/23.
//

#include "MapCreator.h"
#include "../../../../Shaders/Lighting/LightSpot.h"
#include "../../../../ExtResources/LessonResources/TextureResources/skycube.h"
#include "../../../../Model/Factory/ModelFactory.h"

void
MapCreator::FourSpheres(const std::string &mapName, std::vector<std::shared_ptr<ShaderHandler>> &shaders, MapManager &mapManager) {

    mapManager.CreateNewMap(mapName);
    std::shared_ptr<Map> &map = mapManager.GetMap(mapName);

    ShaderHandler *PhongShader = SelectShader(shaders, "Phong");
    ShaderHandler *Skybox = SelectShader(shaders, "Skybox");

    std::shared_ptr<StandardisedModel> objectSphere1 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                               "Test model 1");
    objectSphere1->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere1);

    std::shared_ptr<StandardisedModel> objectSphere2 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                               "Test model 2");
    objectSphere2->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere2);

    std::shared_ptr<StandardisedModel> objectSphere3 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                               "Test model 3");
    objectSphere3->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere3);

    std::shared_ptr<StandardisedModel> objectSphere4 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                               "Test model 4");
    objectSphere4->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere4);

    std::shared_ptr<StandardisedModel> objectSphere5 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                               "Test model 5");
    objectSphere5->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere5);

    std::shared_ptr<StandardisedModel> objectSphere6 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                               "Test model 6");
    objectSphere6->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere6);

    std::shared_ptr<StandardisedModel> objectSphere7 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                               "Test model 7");
    objectSphere7->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere7);

    std::shared_ptr<StandardisedModel> objectSphere8 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                               "Test model 8");
    objectSphere8->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere8);

    std::shared_ptr<StandardisedModel> objectSphere9 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                               "Test model 9");
    objectSphere9->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere9);

    std::shared_ptr<StandardisedModel> objectSphere10 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                                "Test model 10");
    objectSphere10->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere10);

    std::shared_ptr<StandardisedModel> objectSphere11 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                                "Test model 11");
    objectSphere11->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere11);

    std::shared_ptr<StandardisedModel> objectSphere12 = mapManager.ModelObjectController.UseAny("Lesson/cube.obj",
                                                                                                "Test model 12");
    objectSphere12->SetShaderProgram(PhongShader);
    mapManager.AddObjectToMap(map, objectSphere12);

    std::shared_ptr<LightSpot> spotLight = std::make_shared<LightSpot>(glm::vec3(0.0f, 0.0f, 0.0f),
                                                                       glm::vec3(0.0f, 1.0f, 0));
    spotLight->SetOuterCutOff(100.0f);
    map->InsertLight(spotLight);

    objectSphere1->InsertTransfMove(glm::vec3(-2.0f, 0.0f, 0.0f)).
            InsertTransfRotate(90, glm::vec3(-1.0f, 0, 0)).ConsolidateTransf();
    objectSphere2->InsertTransfMove(glm::vec3(0.0f, 0.0f, 2.0f)).ConsolidateTransf();
    objectSphere3->InsertTransfMove(glm::vec3(2.0f, 0.0f, 0.0f)).ConsolidateTransf();
    objectSphere4->InsertTransfMove(glm::vec3(0.0f, 0.0f, -2.0f)).ConsolidateTransf();

    objectSphere5->InsertTransfMove(glm::vec3(-2.0f, 4.0f, 0.0f)).ConsolidateTransf();
    objectSphere6->InsertTransfMove(glm::vec3(0.0f, 4.0f, 2.0f)).ConsolidateTransf();
    objectSphere7->InsertTransfMove(glm::vec3(2.0f, 4.0f, 0.0f)).ConsolidateTransf();
    objectSphere8->InsertTransfMove(glm::vec3(0.0f, 4.0f, -2.0f)).ConsolidateTransf();

    objectSphere9->InsertTransfMove(glm::vec3(-2.0f, -4.0f, 0.0f)).ConsolidateTransf();
    objectSphere10->InsertTransfMove(glm::vec3(0.0f, -4.0f, 2.0f)).ConsolidateTransf();
    objectSphere11->InsertTransfMove(glm::vec3(2.0f, -4.0f, 0.0f)).ConsolidateTransf();
    objectSphere12->InsertTransfMove(glm::vec3(0.0f, -4.0f, -2.0f)).ConsolidateTransf();

    const float *rawmodel_skycube = skycube;
    int skycube_size = sizeof(skycube) / sizeof(float);
    std::shared_ptr<StandardisedModel> pmSkybox = ModelFactory::Position(rawmodel_skycube, skycube_size, "Skybox");
    pmSkybox->SetShaderProgram(Skybox);
    Texture *skyboxTexture = mapManager.TextureObjectsController.UseCubemap("Lesson/FieldSkybox/field");
    pmSkybox->SetTexture(skyboxTexture);
    map->SetSkybox(pmSkybox);
}
