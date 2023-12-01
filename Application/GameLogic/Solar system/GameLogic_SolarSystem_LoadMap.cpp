//
// Created by lvi on 1.12.23.
//

#include "GameLogic_SolarSystem.h"
#include "../../../Transformations/Composite/Factory/TransformationFactory.h"

void GameLogic_SolarSystem::LoadMap() {
    Resources->CreateNewMap("Solar system");
    map = Resources->GetMap("Solar system").get();

    ShaderHandler *ConstantShader = AnyGameLogic::SelectShader(Resources->Shaders, "Constant");
    ShaderHandler *PhongShader = AnyGameLogic::SelectShader(Resources->Shaders, "Phong");
    ShaderHandler *Skybox = AnyGameLogic::SelectShader(Resources->Shaders, "Skybox");

    float earthOrbitSpeed = 0.05f;
    float mercuryOrbitSpeed = 0.02f;
    float venusOrbitSpeed = 0.06f;
    float marsOrbitSpeed = 0.03f;

//    this->ResourceManager.AddLightToMap(1, std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, 0.0f)));
    Resources->AddLightToMap(map, std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, 0.0f)));

    //Sun
    std::shared_ptr<StandardisedModel> objectSun = Resources->ModelObjectController.UseAny("sphere.obj",
                                                                                           "Sun");
    objectSun->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                    glm::vec3(1.0f, 0.5f, 0.0f),
                                    glm::vec3(1.0f, 0.5f, 0.0f),
                                    32.0f));
    objectSun->SetShaderProgram(ConstantShader);
    Resources->AddObjectToMap(map, objectSun);

    //Mercury
    std::shared_ptr<StandardisedModel> objectMercury = Resources->ModelObjectController.UseAny("sphere.obj",
                                                                                               "Mercury");
    objectMercury->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                        glm::vec3(0.5f, 0.5f, 0.5f),
                                        glm::vec3(0.5f, 0.5f, 0.5f),
                                        32.0f));
    objectMercury->SetShaderProgram(PhongShader);
    Resources->AddObjectToMap(map, objectMercury);
    //Move mercury away from the sun, and make it smaller permanently.
    objectMercury->InsertTransfScale(glm::vec3(0.15f, 0.15f, 0.15f))
            .InsertTransfMove(glm::vec3(10.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectMercury->InsertTransfComposite(
            TransformationFactory::CreateOrbit(glm::vec3(-10.0f, 0.0f, 0.0f),
                                               mercuryOrbitSpeed,
                                               glm::vec3(0.0f, 1.0f, 0.0f)));

    //Venus
    std::shared_ptr<StandardisedModel> objectVenus = Resources->ModelObjectController.UseAny("sphere.obj",
                                                                                             "Venus");
    objectVenus->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.5f, 0.0f),
                                      glm::vec3(1.0f, 0.5f, 0.0f), 32.0f));
    objectVenus->SetShaderProgram(PhongShader);
    Resources->AddObjectToMap(map, objectVenus);

    //Move venus away from the sun, and make it smaller permanently.
    objectVenus->InsertTransfScale(glm::vec3(0.2f, 0.2f, 0.2f))
            .InsertTransfMove(glm::vec3(15.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectVenus->InsertTransfComposite(
            TransformationFactory::CreateOrbit(glm::vec3(-15.0f, 0.0f, 0.0f),
                                               venusOrbitSpeed,
                                               glm::vec3(0.0f, 1.0f, 0.0f)));

    //Earth
    std::shared_ptr<StandardisedModel> objectEarth = Resources->ModelObjectController.UseAny("sphere.obj",
                                                                                             "Earth");
    Resources->AddObjectToMap(map, objectEarth);
    Earth = objectEarth.get();

    Earth->SetMaterial(Material(
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(0.0f, 0.5f, 1.0f),
            glm::vec3(0.0f, 0.5f, 1.0f), 240.0f));
    Earth->SetShaderProgram(PhongShader);


    //Move earth away from the sun, and make it smaller permanently.
    Earth->InsertTransfScale(glm::vec3(0.2f, 0.2f, 0.2f))
            .InsertTransfMove(glm::vec3(30.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    Earth->InsertTransfComposite(
            TransformationFactory::CreateOrbit(glm::vec3(-30.0f, 0.0f, 0.0f),
                                               earthOrbitSpeed,
                                               glm::vec3(0.0f, 1.0f, 0.0f)));

    //Moon
    std::shared_ptr<StandardisedModel> objectMoon = Resources->ModelObjectController.UseAny("sphere.obj",
                                                                                            "Moon");
    Resources->AddObjectToMap(map, objectMoon);

    Moon = objectMoon.get();
    Moon->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f),
                               glm::vec3(0.5f, 0.5f, 0.5f), 32.0f));
    Moon->SetShaderProgram(PhongShader);

    //Mars
    std::shared_ptr<StandardisedModel> objectMars = Resources->ModelObjectController.UseAny("sphere.obj",
                                                                                            "Mars");
    objectMars->SetMaterial(Material(
            glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3(1.0f, 0.5f, 0.0f),
            glm::vec3(1.0f, 0.5f, 0.0f),
            32.0f));
    objectMars->SetShaderProgram(PhongShader);
    Resources->AddObjectToMap(map, objectMars);

    //Move mars away from the sun, and make it smaller permanently.
    objectMars->InsertTransfScale(glm::vec3(0.2f, 0.2f, 0.2f))
            .InsertTransfMove(glm::vec3(45.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectMars->InsertTransfComposite(TransformationFactory::CreateOrbit(glm::vec3(-45.0f, 0.0f, 0.0f),
                                                                         marsOrbitSpeed,
                                                                         glm::vec3(0.0f, 1.0f, 0.0f)));

    //Skybox
    std::shared_ptr<StandardisedModel> starSkybox = Resources->ModelObjectController.UsePosition("skybox.obj", "Starbox");

    starSkybox->SetShaderProgram(Skybox);
    Texture *starSkyboxTexture = Resources->TextureObjectsController.UseCubemap(
            "../Resources/Textures/Galaxy/stars", false);
    starSkybox->SetTexture(starSkyboxTexture);
    Resources->AddSkyboxToMap(map, starSkybox);
}