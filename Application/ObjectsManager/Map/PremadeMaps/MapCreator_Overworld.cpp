//
// Created by lvi on 11/18/23.
//

#include "MapCreator.h"
#include "../../../../ExtResources/LessonResources/InclLessonModels.h"
#include "../../../../Shaders/Lighting/LightSpot.h"
#include "../../../../Shaders/Lighting/LightDirectional.h"
#include "../../../../Model/Factory/ModelFactory.h"
#include "../../../../Transformations/Composite/Transformations/Move.h"
#include "../../../../Transformations/Composite/Transformations/Rotate.h"
#include "../../../../Transformations/Composite/Transformations/Scale.h"
#include "../../../../Transformations/Composite/Factory/TransformationFactory.h"

void MapCreator::Overworld(const std::string &mapName, std::vector<std::shared_ptr<ShaderHandler>> &shaders, MapManager &mapManager) {
    mapManager.CreateNewMap(mapName);
    std::shared_ptr<Map> &map = mapManager.GetMap(mapName);

    const float *rawmodel1_sphere = sphere;
    int size = sizeof(sphere) / sizeof(float);

    const float *rawmodel2_tree = tree;
    int size2 = sizeof(tree) / sizeof(float);

    const float *rawmodel3_suziSmooth = suziSmooth;
    int size3 = sizeof(suziSmooth) / sizeof(float);

    const float *rawmodel4_bushes = bushes;
    int size4 = sizeof(bushes) / sizeof(float);

    const float *rawmodel5_suziFlat = suziFlat;
    int size5 = sizeof(suziFlat) / sizeof(float);

    const float *rawmodel6_plain = plain;
    int size6 = sizeof(plain) / sizeof(float);

    const float *rawmodel7_gift = gift;
    int size7 = sizeof(gift) / sizeof(float);

    const float *rawmodel9_plane_text = plane_tex;
    int size9 = sizeof(plane_tex) / sizeof(float);


    ShaderHandler *ConstantShader = SelectShader(shaders, "Constant");
    ShaderHandler *PhongShader = SelectShader(shaders, "Phong");
    ShaderHandler *BlinnPhongShader = SelectShader(shaders, "BlinnPhong");
    ShaderHandler *LambertShader = SelectShader(shaders, "Lambert");
    ShaderHandler *PhongTextureShader = SelectShader(shaders, "PhongTexture");
    ShaderHandler *SkyboxShader = SelectShader(shaders, "Skybox");

    const float *rawmodels[] = {rawmodel1_sphere, rawmodel2_tree, rawmodel3_suziSmooth, rawmodel4_bushes,
                                rawmodel5_suziFlat, rawmodel6_plain, rawmodel7_gift};
    int sizes[] = {size, size2, size3, size4, size5, size6, size7};
    int totalArraySizes = 7;


    std::shared_ptr<LightSpot> flashLight = std::make_shared<LightSpot>(glm::vec3(0.0f, 5.0f, 10.0f),
                                                                        glm::vec3(0.0f, -1.0f, 0.0f));
    mapManager.AddLightToMap(map, flashLight);
//    flashLight->SetColor(glm::vec3(0.0f, 0.0f, 0.0f));


    std::shared_ptr<LightDirectional> directionalLight = std::make_shared<LightDirectional>(
            glm::vec3(0.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f));
    directionalLight->SetColor(glm::vec3(0.9f, 0.9f, 0.9f));

//    mapManager.AddLightToMap(map, directionalLight);


    std::dynamic_pointer_cast<LightSpot>(mapManager.GetLightOnMap(map, 0))
            ->SetQuadratic(0.0001f)
            .SetIntensity(1.0f);

    std::shared_ptr<StandardisedModel> preparedModelGround = mapManager.ModelObjectController.UseAny("Lesson/plane.obj");
    preparedModelGround->SetShaderProgram(PhongTextureShader);
    preparedModelGround->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                              glm::vec3(0.5f, 0.5f, 0.5f),
                                              glm::vec3(0.5f, 0.5f, 0.5f),
                                              32.0f));
    Texture *groundTexture = mapManager.TextureObjectsController.UseTexture("grassHigh.jpg");
    preparedModelGround->SetTexture(groundTexture);
    preparedModelGround->SetMaterial(Material(glm::vec3(0.01f, 0.01f, 0.01f),
                                              glm::vec3(0.5f, 0.5f, 0.5f),
                                              glm::vec3(0.0f, 0.0f, 0.0f),
                                              4.0f));

    preparedModelGround->InsertTransfMove(glm::vec3(0, -1.0f, 0))
            .InsertTransfScale(glm::vec3(100, 100, 100))
            .ConsolidateTransf();

    mapManager.AddObjectToMap(map, preparedModelGround);


    //Zombie
    for (int i = 0; i < 30; i++) {
        std::string name = "Zombie" + std::to_string(i);
        float x = (rand() % 100) - 50;
        float z = (rand() % 100) - 50;
        float rotation = (rand() % 360);

        std::shared_ptr<StandardisedModel> zombie = mapManager.ModelObjectController.UseAny("Lesson/zombie.obj", name);
        zombie->SetShaderProgram(PhongTextureShader);
        zombie->SetTexture(mapManager.TextureObjectsController.UseTexture("Lesson/zombie.png"));
        zombie->InsertTransfMove(glm::vec3(x, -1.0f, z))
                .InsertTransfRotate(rotation, glm::vec3(0, rotation, 0))
                .ConsolidateTransf();
        zombie->SetMaterial(Material());
        mapManager.AddObjectToMap(map, zombie);

        zombie->InsertTransfComposite(TransformationFactory::CreateOrbit(glm::vec3(x, -1.0f, z),
                                                                         0.03f,
                                                                         glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    //Shed
    std::shared_ptr<StandardisedModel> shed = mapManager.ModelObjectController.UseAny("Lesson/model.obj");
    shed->SetShaderProgram(PhongTextureShader);
    shed->SetTexture(mapManager.TextureObjectsController.UseTexture("Lesson/building.png"));
    shed->InsertTransfMove(glm::vec3(10, -1.0f, 0)).ConsolidateTransf();
    shed->SetMaterial(Material());
    mapManager.AddObjectToMap(map, shed);

    //Tree
    for (int i = 0; i < 60; ++i) {
        float x = (rand() % 100) - 50;
        float z = (rand() % 100) - 50;

        std::string name = "Tree" + std::to_string(i);

        std::shared_ptr<StandardisedModel> tree = mapManager.ModelObjectController.UseAny("Tree1.3ds", name);
        tree->SetShaderProgram(PhongTextureShader);
        tree->InsertTransfMove(glm::vec3(x, -1.0f, z))
                .InsertTransfRotate(90, glm::vec3(-1.0f, 0, 0))
                .InsertTransfScale(glm::vec3(0.5f, 0.5f, 0.5f))
                .ConsolidateTransf();
        tree->SetTexture(mapManager.TextureObjectsController.UseTexture("bark.jpg"));
        tree->ChildObjects.at(0)->SetTexture(mapManager.TextureObjectsController.UseTexture("bark.jpg"));
        tree->ChildObjects.at(1)->SetTexture(mapManager.TextureObjectsController.UseTexture("bark.jpg"));
        tree->ChildObjects.at(2)->SetTexture(mapManager.TextureObjectsController.UseTexture("bark.jpg"));
        tree->ChildObjects.at(3)->SetTexture(mapManager.TextureObjectsController.UseTexture("leaves.jpg"));
        tree->ChildObjects.at(4)->SetTexture(mapManager.TextureObjectsController.UseTexture("leaves.jpg"));
        mapManager.AddObjectToMap(map, tree);
    }


    //Street lamp material
    Material streetLampMaterial;
    streetLampMaterial.DiffuseColor = glm::vec3(0.3f, 0.3f, 0.3f);
    streetLampMaterial.SpecularColor = glm::vec3(0.5f, 0.5f, 0.5f);
    streetLampMaterial.ShineValue = 32.0f;

    std::shared_ptr<TransfComposite> streetLampMoveComposite = std::make_shared<TransfComposite>();
    streetLampMoveComposite->Insert(std::make_shared<Move>(glm::vec3(-5, 2.5f, -20)));

    std::shared_ptr<TransfComposite> streetLampComposite = std::make_shared<TransfComposite>();
    streetLampComposite->Insert(streetLampMoveComposite);
    streetLampComposite->Insert(std::make_shared<Scale>(glm::vec3(0.008f, 0.008f, 0.008f)));

    //Bulb
    std::shared_ptr<TransfComposite> bulbToLamp = std::make_shared<TransfComposite>();
    bulbToLamp->Insert(std::make_shared<Move>(glm::vec3(3.45f, 8.8f, 0.0f)));
    bulbToLamp->Insert(std::make_shared<Scale>(glm::vec3(0.42f, 0.17f, 0.3f)));


    std::shared_ptr<StandardisedModel> streetLampBulb = ModelFactory::PositionNormal(rawmodel1_sphere, size, "Bulb");
    streetLampBulb->SetShaderProgram(ConstantShader);
    streetLampBulb->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                         glm::vec3(1.0f, 1.0f, 0.0f),
                                         glm::vec3(1.0f, 1.0f, 1.0f),
                                         32.0f));
    streetLampBulb->InsertTransfComposite(streetLampMoveComposite);
    streetLampBulb->InsertTransfComposite(bulbToLamp);
    streetLampBulb->ConsolidateTransf();
    mapManager.AddObjectToMap(map, streetLampBulb);

    //Light
    std::shared_ptr<LightPoint> streetLampLight = std::make_shared<LightPoint>(glm::vec3(-1.0f, 3.0f, -20.0f));
    streetLampLight->SetIntensity(1.0f);
    streetLampLight->SetConstant(1.0f);
    streetLampLight->SetLinear(0.1f);
    streetLampLight->SetQuadratic(0.01f);
    mapManager.AddLightToMap(map, streetLampLight);


    //Street lamp
    std::shared_ptr<StandardisedModel> streetLamp = mapManager.ModelObjectController.UsePositionNormalTex(
            "Street_Lamp.obj");
    streetLamp->SetShaderProgram(PhongShader);
    streetLamp->InsertTransfComposite(streetLampComposite);
    streetLamp->ConsolidateTransf();
    streetLamp->SetMaterial(streetLampMaterial);
    for (auto &child: streetLamp->ChildObjects) {
        child->SetMaterial(streetLampMaterial);
    }
    mapManager.AddObjectToMap(map, streetLamp);


    //Skybox
    const float *rawmodel_skycube = skycube;
    int skycube_size = sizeof(skycube) / sizeof(float);
    std::shared_ptr<StandardisedModel> starSkybox = ModelFactory::Position(rawmodel_skycube, skycube_size,
                                                                           "Star skybox");

    starSkybox->SetShaderProgram(SkyboxShader);
    Texture *starSkyboxTexture = mapManager.TextureObjectsController.UseCubemap(
            "starbox");
    starSkybox->SetTexture(starSkyboxTexture);
    MapManager::AddSkyboxToMap(map, starSkybox);
}