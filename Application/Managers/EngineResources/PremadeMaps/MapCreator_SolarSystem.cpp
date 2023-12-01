//
// Created by lvi on 11/18/23.
//

#include "MapCreator.h"
#include "../../../../Model/Factory/ModelFactory.h"
#include "../../../../Transformations/Composite/Factory/TransformationFactory.h"

void
MapCreator::SolarSystem(std::vector<std::shared_ptr<ShaderHandler>> &shaders, ResourcesManager *mapManager) {
    mapManager->CreateNewMap("Solar system");
    std::shared_ptr<Map> &map = mapManager->GetMap("Solar system");

    ShaderHandler *ConstantShader = SelectShader(shaders, "Constant");
    ShaderHandler *PhongShader = SelectShader(shaders, "Phong");
    ShaderHandler *Skybox = SelectShader(shaders, "Skybox");

    float earthOrbitSpeed = 0.05f;
    float mercuryOrbitSpeed = 0.02f;
    float venusOrbitSpeed = 0.06f;
    float marsOrbitSpeed = 0.03f;

//    this->ResourceManager.AddLightToMap(1, std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, 0.0f)));
    mapManager->AddLightToMap(map, std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, 0.0f)));

    //Sun
    std::shared_ptr<StandardisedModel> objectSun = mapManager->ModelObjectController.UseAny("sphere.obj",
                                                                                            "Sun");
    objectSun->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                    glm::vec3(1.0f, 0.5f, 0.0f),
                                    glm::vec3(1.0f, 0.5f, 0.0f),
                                    32.0f));
    objectSun->SetShaderProgram(ConstantShader);
    mapManager->AddObjectToMap(map, objectSun);

    //Mercury
    std::shared_ptr<StandardisedModel> objectMercury = mapManager->ModelObjectController.UseAny("sphere.obj",
                                                                                                "Mercury");
    objectMercury->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                        glm::vec3(0.5f, 0.5f, 0.5f),
                                        glm::vec3(0.5f, 0.5f, 0.5f),
                                        32.0f));
    objectMercury->SetShaderProgram(PhongShader);
    mapManager->AddObjectToMap(map, objectMercury);
    //Move mercury away from the sun, and make it smaller permanently.
    objectMercury->InsertTransfScale(glm::vec3(0.15f, 0.15f, 0.15f))
            .InsertTransfMove(glm::vec3(10.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectMercury->InsertTransfComposite(
            TransformationFactory::CreateOrbit(glm::vec3(-10.0f, 0.0f, 0.0f),
                                               mercuryOrbitSpeed,
                                               glm::vec3(0.0f, 1.0f, 0.0f)));

    //Venus
    std::shared_ptr<StandardisedModel> objectVenus = mapManager->ModelObjectController.UseAny("sphere.obj",
                                                                                              "Venus");
    objectVenus->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.5f, 0.0f),
                                      glm::vec3(1.0f, 0.5f, 0.0f), 32.0f));
    objectVenus->SetShaderProgram(PhongShader);
    mapManager->AddObjectToMap(map, objectVenus);

    //Move venus away from the sun, and make it smaller permanently.
    objectVenus->InsertTransfScale(glm::vec3(0.2f, 0.2f, 0.2f))
            .InsertTransfMove(glm::vec3(15.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectVenus->InsertTransfComposite(
            TransformationFactory::CreateOrbit(glm::vec3(-15.0f, 0.0f, 0.0f),
                                               venusOrbitSpeed,
                                               glm::vec3(0.0f, 1.0f, 0.0f)));

    //Earth
    std::shared_ptr<StandardisedModel> objectEarth = mapManager->ModelObjectController.UseAny("sphere.obj",
                                                                                              "Earth");
    objectEarth->SetMaterial(Material(
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.0f, 0.5f, 1.0f),
            glm::vec3(0.0f, 0.5f, 1.0f), 240.0f));
    objectEarth->SetShaderProgram(PhongShader);
    mapManager->AddObjectToMap(map, objectEarth);

    //Move earth away from the sun, and make it smaller permanently.
    objectEarth->InsertTransfScale(glm::vec3(0.2f, 0.2f, 0.2f))
            .InsertTransfMove(glm::vec3(30.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectEarth->InsertTransfComposite(
            TransformationFactory::CreateOrbit(glm::vec3(-30.0f, 0.0f, 0.0f),
                                               earthOrbitSpeed,
                                               glm::vec3(0.0f, 1.0f, 0.0f)));

    //Moon
    std::shared_ptr<StandardisedModel> objectMoon = mapManager->ModelObjectController.UseAny("sphere.obj",
                                                                                             "Moon");
    objectMoon->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f),
                                     glm::vec3(0.5f, 0.5f, 0.5f), 32.0f));
    objectMoon->SetShaderProgram(PhongShader);
    mapManager->AddObjectToMap(map, objectMoon);

    //Mars
    std::shared_ptr<StandardisedModel> objectMars = mapManager->ModelObjectController.UseAny("sphere.obj",
                                                                                             "Mars");
    objectMars->SetMaterial(Material(
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(1.0f, 0.5f, 0.0f),
            glm::vec3(1.0f, 0.5f, 0.0f),
            32.0f));
    objectMars->SetShaderProgram(PhongShader);
    mapManager->AddObjectToMap(map, objectMars);

    //Move mars away from the sun, and make it smaller permanently.
    objectMars->InsertTransfScale(glm::vec3(0.2f, 0.2f, 0.2f))
            .InsertTransfMove(glm::vec3(45.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectMars->InsertTransfComposite(TransformationFactory::CreateOrbit(glm::vec3(-45.0f, 0.0f, 0.0f),
                                                                         marsOrbitSpeed,
                                                                         glm::vec3(0.0f, 1.0f, 0.0f)));

    //Skybox
    std::shared_ptr<StandardisedModel> starSkybox = mapManager->ModelObjectController.UsePosition("skybox.obj", "Starbox");

    starSkybox->SetShaderProgram(Skybox);
    Texture *starSkyboxTexture = mapManager->TextureObjectsController.UseCubemap(
            "../Resources/Textures/Galaxy/stars", false);
    starSkybox->SetTexture(starSkyboxTexture);
    ResourcesManager::AddSkyboxToMap(map, starSkybox);
}