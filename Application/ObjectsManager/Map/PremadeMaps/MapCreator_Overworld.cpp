//
// Created by lvi on 11/18/23.
//

#include "MapCreator.h"
#include "../../../../ExtResources/LessonResources/InclLessonModels.h"
#include "../../../../Shaders/Lighting/LightSpot.h"
#include "../../../../Shaders/Lighting/LightDirectional.h"
#include "../../../../Model/Factory/ModelFactory.h"

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

    const float *rawmodel8_skycube = skycube;
    int size8 = sizeof(skycube) / sizeof(float);

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

    srand(static_cast<unsigned int>(time(nullptr)));
    auto randomModel = [&rawmodels, &sizes, &totalArraySizes]() -> std::pair<const float *, int> {
        int index = rand() % totalArraySizes;
        return std::make_pair(rawmodels[index], sizes[index]);
    };

    auto randomMaterial = []() -> Material {
        Material material;
        material.AmbientColor = glm::vec3(0.1f, 0.1f, 0.1f);
        material.DiffuseColor = glm::vec3((float) rand() / RAND_MAX, (float) rand() / RAND_MAX,
                                          (float) rand() / RAND_MAX);
        material.SpecularColor = glm::vec3((float) rand() / RAND_MAX, (float) rand() / RAND_MAX,
                                           (float) rand() / RAND_MAX);
        material.ShineValue = (float) rand() / RAND_MAX * 245 + 10;
        return material;
    };

    mapManager.AddLightToMap(map, std::make_shared<LightSpot>(glm::vec3(0.0f, 5.0f, 10.0f),
                                                              glm::vec3(0.0f, -1.0f, 0.0f)));

    std::shared_ptr<LightDirectional> directionalLight = std::make_shared<LightDirectional>(
            glm::vec3(0.0f, -1.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f));
    directionalLight->SetColor(glm::vec3(0.3f, 0.3f, 0.3f));

    mapManager.AddLightToMap(map, directionalLight);


    std::dynamic_pointer_cast<LightSpot>(mapManager.GetLightOnMap(map, 0))
            ->SetQuadratic(0.0001f)
            .SetIntensity(1.0f);

    std::shared_ptr<StandardisedModel> preparedModelGround = ModelFactory::PositionNormalTex(rawmodel9_plane_text,
                                                                                             size9,
                                                                                             "Ground");
    preparedModelGround->SetShaderProgram(PhongTextureShader);
    preparedModelGround->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f),
                                              glm::vec3(0.5f, 0.5f, 0.5f), 32.0f));
    Texture *groundTexture = mapManager.TextureObjectsController.UseTexture(
            "Lesson/grass.png");
    preparedModelGround->SetTexture(groundTexture);

    preparedModelGround->InsertTransfMove(glm::vec3(0, -1.0f, 0))
            .InsertTransfRotate(-90, glm::vec3(1, 0, 0))
            .InsertTransfScale(glm::vec3(100, 100, 100))
            .ConsolidateTransf();

    mapManager.AddObjectToMap(map, preparedModelGround);


    auto add100RandomObject = [&randomModel, &randomMaterial, &mapManager, &mapName](ShaderHandler *shader) -> void {
        for (int i = 0; i < 100; i++) {
            std::pair<const float *, int> randomModelPair = randomModel();

            std::shared_ptr<StandardisedModel> randomObjectsPhong = ModelFactory::PositionNormal(randomModelPair.first,
                                                                                                 randomModelPair.second,
                                                                                                 "Random object p1, " +
                                                                                                 std::to_string(i));
            randomObjectsPhong->SetShaderProgram(shader);
            randomObjectsPhong->SetMaterial(randomMaterial());
            float randomScale = (float) rand() / RAND_MAX * 2 + 0.5f;
            randomObjectsPhong->InsertTransfMove(
                    glm::vec3((float) rand() / RAND_MAX * 100 - 50, -0.9f,
                              (float) rand() / RAND_MAX * 100 - 50)).InsertTransfRotate(
                    (float) rand() / RAND_MAX * 360, glm::vec3(0.0f, 1.0f, 0.0f)).
                    InsertTransfScale(glm::vec3(randomScale, randomScale, randomScale)).ConsolidateTransf();
            mapManager.AddObjectToMap(mapName, randomObjectsPhong);
        }
    };

    add100RandomObject(PhongShader);
    add100RandomObject(LambertShader);
    add100RandomObject(BlinnPhongShader);
//    add100RandomObject(SelectShader("Constant"));
}