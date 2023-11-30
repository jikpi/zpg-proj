//
// Created by lvi on 11/18/23.
//

#include "MapCreator.h"
#include "../../../../ExtResources/LessonResources/SecondModels/sphere.h"
#include "../../../../Model/Factory/ModelFactory.h"
#include "../../../../Transformations/Composite/Factory/TransformationFactory.h"
#include "../../../../ExtResources/LessonResources/TextureResources/skycube.h"

void
MapCreator::SolarSystem(const std::string &mapName, std::vector<std::shared_ptr<ShaderHandler>> &shaders, ResourcesManager *mapManager) {
    mapManager->CreateNewMap(mapName);
    std::shared_ptr<Map> &map = mapManager->GetMap(mapName);

    ShaderHandler *ConstantShader = SelectShader(shaders, "Constant");
    ShaderHandler *PhongShader = SelectShader(shaders, "Phong");
    ShaderHandler *Skybox = SelectShader(shaders, "Skybox");

    const float *rawmodel1_sphere = sphere;
    int size = sizeof(sphere) / sizeof(float);

    float earthOrbitSpeed = 0.05f;
    float mercuryOrbitSpeed = 0.02f;
    float venusOrbitSpeed = 0.06f;
    float marsOrbitSpeed = 0.03f;

//    this->ResourceManager.AddLightToMap(1, std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, 0.0f)));
    mapManager->AddLightToMap(map, std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, 0.0f)));

    //Sun
    std::shared_ptr<StandardisedModel> objectSun = ModelFactory::PositionNormal(rawmodel1_sphere, size, "Sun");
    objectSun->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                    glm::vec3(1.0f, 0.5f, 0.0f),
                                    glm::vec3(1.0f, 0.5f, 0.0f),
                                    32.0f));
    objectSun->SetShaderProgram(ConstantShader);
    mapManager->AddObjectToMap(map, objectSun);

    //Mercury
    std::shared_ptr<StandardisedModel> objectMercury = ModelFactory::PositionNormal(rawmodel1_sphere, size, "Mercury");
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
    std::shared_ptr<StandardisedModel> objectVenus = ModelFactory::PositionNormal(rawmodel1_sphere, size, "Venus");
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
    std::shared_ptr<StandardisedModel> objectEarth = ModelFactory::PositionNormal(rawmodel1_sphere, size, "Earth");
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

    //Mars
    std::shared_ptr<StandardisedModel> objectMars = ModelFactory::PositionNormal(rawmodel1_sphere, size, "Mars");
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
    const float *rawmodel_skycube = skycube;
    int skycube_size = sizeof(skycube) / sizeof(float);
    std::shared_ptr<StandardisedModel> starSkybox = ModelFactory::Position(rawmodel_skycube, skycube_size,
                                                                           "Star skybox");

    starSkybox->SetShaderProgram(Skybox);
    Texture *starSkyboxTexture = mapManager->TextureObjectsController.UseCubemap(
            "../Resources/Textures/Galaxy/stars", false);
    starSkybox->SetTexture(starSkyboxTexture);
    ResourcesManager::AddSkyboxToMap(map, starSkybox);
}