//
// Created by KOP0269 on 25.9.23.
//

#include "Engine.h"
#include "../Model/Factory/ModelFactory.h"
#include "DebugErrorMessages/DebugErrorMessages.h"
#include "../Shaders/ShadersCode/Loader/ShaderFileLoader.h"

#include <cmath>
#include <utility>
#include "InputHandler/KeyCallbacks/KeyCallbacks.h"
#include "../Transformations/Composite/TransfComposite.h"
#include "../Transformations/Composite/Transformations/Rotate.h"
#include "../Transformations/Composite/Transformations/Scale.h"
#include "../Transformations/Composite/Transformations/Move.h"

//Shaders
#include "../Shaders/ShaderProgram/ShaderHandlerFactory/ShaderHandlerFactory.h"

//Transformations
#include "../Transformations/Composite/Factory/TransformationFactory.h"

//Models
#include "../ExtResources/LessonResources/InclLessonModels.h"
#include "../Shaders/Lighting/LightDirectional.h"
#include "../Shaders/Lighting/LightSpot.h"


Engine::Engine() = default;

void Engine::Initialize() {
    glfwSetErrorCallback(KeyCallbacks::error_callback);

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    //Initialize version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE);
    //Enable debug
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    //Depth hint
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    //Create window
    Window = glfwCreateWindow(640, 480, "ZPG KOP0269", nullptr, nullptr);
    if (!Window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(Window);
    glfwSwapInterval(1);

    //Start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    //Enable debug context
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugErrorMessages::ErrorCallback, nullptr);

    //Inputs
    InitializeInputHandling();

//    Culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //Depth
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glfwGetFramebufferSize(Window, &Width, &Height);
    Ratio = Width / (float) Height;
    glViewport(0, 0, Width, Height);


    //Camera lock
    glfwSetCursorPosCallback(Window, KeyCallbacks::cursor_callback);
//    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Map
    this->EngineMapManager.Initialize();
}

void Engine::InitializeInputHandling() {
    KeyCallbacks::Engines = std::weak_ptr<Engine>(shared_from_this());

    MovesetManager = std::make_shared<MovesetInputManager>();
    MovesetManager->Register();


    glfwSetKeyCallback(Window, KeyCallbacks::key_callback);
    glfwSetCursorPosCallback(Window, KeyCallbacks::cursor_callback);
    glfwSetMouseButtonCallback(Window, KeyCallbacks::button_callback);
    glfwSetWindowFocusCallback(Window, KeyCallbacks::window_focus_callback);
    glfwSetWindowIconifyCallback(Window, KeyCallbacks::window_iconify_callback);
    glfwSetWindowSizeCallback(Window, KeyCallbacks::window_size_callback);
}

void Engine::NotifyWindowResize(int newWidth, int newHeight) {
    this->Width = newWidth;
    this->Height = newHeight;
    if (newHeight == 0) {
        newHeight = 1;
    }

    this->Ratio = newWidth / (float) newHeight;
    glViewport(0, 0, newWidth, newHeight);

    if (this->CameraMain != nullptr) {
        this->CameraMain->SetAspectRatio(this->Ratio);
    }
}

void Engine::PrintVersionInfo() {
    // get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n\n", major, minor, revision);
    printf("Move camera with 'wasd' and 'r,f', press 'c' to toggle camera, 'y' to toggle movement method, '1-9' to change the map, 'p' to toggle perspective, 'm' to set random materials for objects.\n");
}

void Engine::Run() {
    this->SetCameraLock(true);
    DebugErrorMessages::PrintGLErrors("Before run errors");


    float radius = 1.0f;
    float angle = 0.0f;
    float angleIncrement = glm::radians(1.0f);

    std::shared_ptr<LightSpot> spheresSpotLight = std::dynamic_pointer_cast<LightSpot>(
            this->EngineMapManager.GetLightOnMap("Default", 0));

    std::shared_ptr<LightSpot> manyObjectsSpotLight = std::dynamic_pointer_cast<LightSpot>(
            this->EngineMapManager.GetLightOnMap("Many objects", 0));

    this->CameraMain->MoveForwardBackward(0);
    this->EngineMapManager.ForceRefreshMaps();
    while (!glfwWindowShouldClose(Window)) {
        //Update camera position
        UpdateMoveset();

        //Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //animate mercury
        this->EngineMapManager.GetMapByIndex(1)->GetObjectByName("Mercury")->DoTransf();
        //animate venus
        this->EngineMapManager.GetMapByIndex(1)->GetObjectByName("Venus")->DoTransf();
        //animate earth
        this->EngineMapManager.GetMapByIndex(1)->GetObjectByName("Earth")->DoTransf();
        //animate mars
        this->EngineMapManager.GetMapByIndex(1)->GetObjectByName("Mars")->DoTransf();


        angle += angleIncrement;
        if (angle > 2 * glm::pi<float>()) {
            angle -= 2 * glm::pi<float>();
        }

        float x = radius * cos(angle);
        float z = radius * sin(angle);

        spheresSpotLight->SetDirection(glm::vec3(x, 0.0f, z));
        manyObjectsSpotLight->SetDirection(glm::vec3(x, 0.0f, z));
        EngineMapManager.ForceRefreshLightsOnCurrentMap();



        //Render each shader
        for (auto &set: this->EngineMapManager.ShaderLinker) {
            set->Shader->UseProgram();

            //Render objects for chosen shader
            for (auto &object: set->Objects) {
                set->Shader->RequestRender(*object);
                object->BindVertexArray();
                glDrawArrays(GL_TRIANGLES, 0, object->GetRenderingSize());
            }

            set->Shader->StopProgram();
        }

        glfwPollEvents();
        glfwSwapBuffers(Window);
    }

}

void Engine::KillWindow() const {
    glfwDestroyWindow(Window);
}

void Engine::TestLaunch() {

    //Camera
    this->CameraMain = std::make_shared<Camera>();
    this->CameraMain->SetAspectRatio(this->Ratio);


    //Shaders
    this->Shaders.push_back(ShaderHandlerFactory::Phong());
    this->EngineMapManager.SetFallbackShader(SelectShader("Phong"));
    this->CameraMain->RegisterCameraObserver(SelectShader("Phong"));

    this->Shaders.push_back(ShaderHandlerFactory::Lambert());
    this->CameraMain->RegisterCameraObserver(SelectShader("Lambert"));

    this->Shaders.push_back(ShaderHandlerFactory::ConstantColored());
    this->CameraMain->RegisterCameraObserver(SelectShader("Constant"));

    this->Shaders.push_back(ShaderHandlerFactory::BlinnPhong());
    this->CameraMain->RegisterCameraObserver(SelectShader("BlinnPhong"));

    //Models

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


    std::shared_ptr<ShaderHandler> &ConstantShader = SelectShader("Constant");
    std::shared_ptr<ShaderHandler> &PhongShader = SelectShader("Phong");
    std::shared_ptr<ShaderHandler> &BlinnPhongShader = SelectShader("BlinnPhong");
    std::shared_ptr<ShaderHandler> &LambertShader = SelectShader("Lambert");

    //Map 1 - 4 spheres and light
    std::shared_ptr<StandardisedModel> objectSphere1 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                    "Test model 1");
    objectSphere1->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere1);

    std::shared_ptr<StandardisedModel> objectSphere2 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                    "Test model 2");
    objectSphere2->SetShaderProgram(BlinnPhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere2);

    std::shared_ptr<StandardisedModel> objectSphere3 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                    "Test model 3");
    objectSphere3->SetShaderProgram(LambertShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere3);

    std::shared_ptr<StandardisedModel> objectSphere4 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                    "Test model 4");
    objectSphere4->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere4);

    std::shared_ptr<StandardisedModel> objectSphere5 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                    "Test model 5");
    objectSphere5->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere5);

    std::shared_ptr<StandardisedModel> objectSphere6 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                    "Test model 6");
    objectSphere6->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere6);

    std::shared_ptr<StandardisedModel> objectSphere7 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                    "Test model 7");
    objectSphere7->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere7);

    std::shared_ptr<StandardisedModel> objectSphere8 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                    "Test model 8");
    objectSphere8->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere8);

    std::shared_ptr<StandardisedModel> objectSphere9 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                    "Test model 9");
    objectSphere9->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere9);

    std::shared_ptr<StandardisedModel> objectSphere10 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                     "Test model 10");
    objectSphere10->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere10);

    std::shared_ptr<StandardisedModel> objectSphere11 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                     "Test model 11");
    objectSphere11->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere11);

    std::shared_ptr<StandardisedModel> objectSphere12 = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                     "Test model 12");
    objectSphere12->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(0, objectSphere12);

    std::shared_ptr<LightSpot> spotLight = std::make_shared<LightSpot>(glm::vec3(0.0f, 0.0f, 0.0f),
                                                                       glm::vec3(0.0f,
                                                                                 1.0f,
                                                                                 0));
    spotLight->SetOuterCutOff(100.0f);
    EngineMapManager.AddLightToMap(0, spotLight);
    EngineMapManager.GetMapByIndex(0)->GetObject(0)->InsertTransfMove(glm::vec3(-2.0f, 0.0f, 0.0f)).ConsolidateTransf();
    EngineMapManager.GetMapByIndex(0)->GetObject(1)->InsertTransfMove(glm::vec3(0.0f, 0.0f, 2.0f)).ConsolidateTransf();
    EngineMapManager.GetMapByIndex(0)->GetObject(2)->InsertTransfMove(glm::vec3(2.0f, 0.0f, 0.0f)).ConsolidateTransf();
    EngineMapManager.GetMapByIndex(0)->GetObject(3)->InsertTransfMove(glm::vec3(0.0f, 0.0f, -2.0f)).ConsolidateTransf();

    EngineMapManager.GetMapByIndex(0)->GetObject(4)->InsertTransfMove(glm::vec3(-2.0f, 4.0f, 0.0f)).ConsolidateTransf();
    EngineMapManager.GetMapByIndex(0)->GetObject(5)->InsertTransfMove(glm::vec3(0.0f, 4.0f, 2.0f)).ConsolidateTransf();
    EngineMapManager.GetMapByIndex(0)->GetObject(6)->InsertTransfMove(glm::vec3(2.0f, 4.0f, 0.0f)).ConsolidateTransf();
    EngineMapManager.GetMapByIndex(0)->GetObject(7)->InsertTransfMove(glm::vec3(0.0f, 4.0f, -2.0f)).ConsolidateTransf();

    EngineMapManager.GetMapByIndex(0)->GetObject(8)->InsertTransfMove(
            glm::vec3(-2.0f, -4.0f, 0.0f)).ConsolidateTransf();
    EngineMapManager.GetMapByIndex(0)->GetObject(9)->InsertTransfMove(glm::vec3(0.0f, -4.0f, 2.0f)).ConsolidateTransf();
    EngineMapManager.GetMapByIndex(0)->GetObject(10)->InsertTransfMove(
            glm::vec3(2.0f, -4.0f, 0.0f)).ConsolidateTransf();
    EngineMapManager.GetMapByIndex(0)->GetObject(11)->InsertTransfMove(
            glm::vec3(0.0f, -4.0f, -2.0f)).ConsolidateTransf();

    //Map 2 - solar system
    float earthOrbitSpeed = 0.05f;

    float mercuryOrbitSpeed = 0.02f;
    float venusOrbitSpeed = 0.06f;
    float marsOrbitSpeed = 0.03f;

    this->EngineMapManager.CreateNewMap("Solar system");

    this->EngineMapManager.AddLightToMap(1, std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, 0.0f)));

    //Sun
    std::shared_ptr<StandardisedModel> objectSun = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                "Sun");
    objectSun->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.5f, 0.0f),
                                    glm::vec3(1.0f, 0.5f, 0.0f), 32.0f));
    objectSun->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(1, objectSun);

    //Mercury
    std::shared_ptr<StandardisedModel> objectMercury = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                    "Mercury");
    objectMercury->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f),
                                        glm::vec3(0.5f, 0.5f, 0.5f), 32.0f));
    objectMercury->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(1, objectMercury);
    //Move mercury away from the sun, and make it smaller permanently.
    objectMercury->InsertTransfScale(glm::vec3(0.15f, 0.15f, 0.15f)).InsertTransfMove(glm::vec3(10.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectMercury->InsertTransfComposite(
            TransformationFactory::CreateOrbit(glm::vec3(-10.0f, 0.0f, 0.0f), mercuryOrbitSpeed,
                                               glm::vec3(0.0f, 1.0f, 0.0f)));

    //Venus
    std::shared_ptr<StandardisedModel> objectVenus = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                  "Venus");
    objectVenus->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.5f, 0.0f),
                                      glm::vec3(1.0f, 0.5f, 0.0f), 32.0f));
    objectVenus->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(1, objectVenus);

    //Move venus away from the sun, and make it smaller permanently.

    objectVenus->InsertTransfScale(glm::vec3(0.2f, 0.2f, 0.2f)).InsertTransfMove(glm::vec3(15.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectVenus->InsertTransfComposite(
            TransformationFactory::CreateOrbit(glm::vec3(-15.0f, 0.0f, 0.0f), venusOrbitSpeed,
                                               glm::vec3(0.0f, 1.0f, 0.0f)));

    //Earth
    std::shared_ptr<StandardisedModel> objectEarth = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                  "Earth");
    objectEarth->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.5f, 1.0f),
                                      glm::vec3(0.0f, 0.5f, 1.0f), 240.0f));
    objectEarth->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(1, objectEarth);

    //Move earth away from the sun, and make it smaller permanently.
    objectEarth->InsertTransfScale(glm::vec3(0.2f, 0.2f, 0.2f)).InsertTransfMove(glm::vec3(30.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectEarth->InsertTransfComposite(
            TransformationFactory::CreateOrbit(glm::vec3(-30.0f, 0.0f, 0.0f), earthOrbitSpeed,
                                               glm::vec3(0.0f, 1.0f, 0.0f)));

    //Mars
    std::shared_ptr<StandardisedModel> objectMars = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                 "Mars");
    objectMars->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 0.5f, 0.0f),
                                     glm::vec3(1.0f, 0.5f, 0.0f), 32.0f));
    objectMars->SetShaderProgram(PhongShader);

    this->EngineMapManager.AddObjectToMap(1, objectMars);
    //Move mars away from the sun, and make it smaller permanently.

    objectMars->InsertTransfScale(glm::vec3(0.2f, 0.2f, 0.2f)).InsertTransfMove(glm::vec3(45.0f, 0.0f, 0.0f))
            .ConsolidateTransf();

    objectMars->InsertTransfComposite(TransformationFactory::CreateOrbit(glm::vec3(-45.0f, 0.0f, 0.0f), marsOrbitSpeed,
                                                                         glm::vec3(0.0f, 1.0f, 0.0f)));


    //Map 3 - 1 sphere and light
    this->EngineMapManager.CreateNewMap("1 sphere");

    std::shared_ptr<StandardisedModel> preparedModelSingleSphere = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                                "Test sphere");
    preparedModelSingleSphere->SetShaderProgram(PhongShader);
    this->EngineMapManager.AddObjectToMap(EngineMapManager.GetMapByName("1 sphere"), preparedModelSingleSphere);

    this->EngineMapManager.AddLightToMap("1 sphere", std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, -3.0f)));

    //Map 4 - Screen aspect ratio test
    this->EngineMapManager.CreateNewMap("Aspect");

    std::shared_ptr<StandardisedModel> preparedModelAspectSphere = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                                "Aspect Sphere");

    preparedModelAspectSphere->SetShaderProgram(PhongShader);
    preparedModelAspectSphere->InsertTransfMove(glm::vec3(3.0f, 0.0f, 0.0f)).ConsolidateTransf();
    this->EngineMapManager.AddObjectToMap("Aspect", preparedModelAspectSphere);

    std::shared_ptr<StandardisedModel> preparedModelAspectGift = ModelFactory::PositionNormal(rawmodel1_sphere, size,
                                                                                              "Aspect Sphere 2");

    preparedModelAspectGift->SetShaderProgram(PhongShader);
    preparedModelAspectGift->InsertTransfMove(glm::vec3(-3.0f, 0.0f, 0.0f)).ConsolidateTransf();
    this->EngineMapManager.AddObjectToMap("Aspect", preparedModelAspectGift);

    this->EngineMapManager.AddLightToMap("Aspect", std::make_shared<LightPoint>(glm::vec3(0.0f, 0.0f, -3.0f)));

    //Map 5 - many objects

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


    this->EngineMapManager.CreateNewMap("Many objects");
    EngineMapManager.AddLightToMap("Many objects", std::make_shared<LightSpot>(glm::vec3(0.0f, 5.0f, 10.0f),
                                                                               glm::vec3(0.0f, -1.0f, 0.0f)));
//    EngineMapManager.AddLightToMap("Many objects", std::make_shared<LightDirectional>(glm::vec3(0.0f, -1.0f, 0.0f),
//                                                                                      glm::vec3(1.0f, 1.0f, 1.0f)));

    std::dynamic_pointer_cast<LightSpot>(EngineMapManager.GetLightOnMap("Many objects", 0))
            ->SetQuadratic(0.0001f)
            .SetIntensity(1.0f);

    std::shared_ptr<StandardisedModel> preparedModelGround = ModelFactory::PositionNormal(rawmodel6_plain, size6,
                                                                                          "Ground");
    preparedModelGround->SetShaderProgram(PhongShader);
    preparedModelGround->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f),
                                              glm::vec3(0.5f, 0.5f, 0.5f), 32.0f));
    preparedModelGround->InsertTransfMove(
            glm::vec3(0, -1.0f, 0)).InsertTransfScale(glm::vec3(100, 100, 100)).ConsolidateTransf();

    EngineMapManager.AddObjectToMap("Many objects", preparedModelGround);


    auto add100RandomObject = [&randomModel, &randomMaterial, this](std::shared_ptr<ShaderHandler> shader) -> void {
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
            EngineMapManager.AddObjectToMap("Many objects", randomObjectsPhong);
        }
    };

    add100RandomObject(SelectShader("Phong"));
    add100RandomObject(SelectShader("Lambert"));
    add100RandomObject(SelectShader("BlinnPhong"));
//    add100RandomObject(SelectShader("Constant"));

}

void Engine::CameraLookHorizontal(double x) {
    if (this->CameraMain != nullptr) {
        this->CameraMain->LookSphericalSide(x);
    }
}

void Engine::CameraLookVertical(double y) {
    if (this->CameraMain != nullptr) {
        this->CameraMain->LookSphericalVertical(y);
    }
}

void Engine::UpdateMoveset() {
    if (this->MovesetManager == nullptr) {
        return;
    }

    if (this->MovesetManager->IsStandStill()) {
        return;
    }

    if (this->CameraMain == nullptr) {
        return;
    }


    float reading;
    reading = this->MovesetManager->ReadForward();
    if (reading != 0) {
        this->CameraMain->MoveForwardBackward(reading);
    }

    reading = this->MovesetManager->ReadSide();
    if (reading != 0) {
        this->CameraMain->MoveSideToSide(reading);
    }

    reading = this->MovesetManager->ReadVertical();
    if (reading != 0) {
        this->CameraMain->MoveUpDown(reading);
    }
}

void Engine::SetCameraLock(bool lock) {
    if (lock) {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        this->CameraMain->UnlockSet(true);
    } else {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        this->CameraMain->UnlockSet(false);
    }
}

void Engine::ToggleCameraLock() {
    if (this->CameraMain->UnlockState()) {
        this->SetCameraLock(false);
    } else {
        this->SetCameraLock(true);
    }
}

void Engine::AddShader(const std::shared_ptr<ShaderHandler> &shader) {
    this->Shaders.push_back(shader);
}

void Engine::ToggleCameraPerspective() {
    if (this->CameraMain == nullptr) {
        return;
    }

    if (this->CameraMain->GetPerspectiveProjection()) {
        this->CameraMain->SetPerspectiveProjection(false);
    } else {
        this->CameraMain->SetPerspectiveProjection(true);
    }
}

void Engine::ToggleCameraYDirection() {
    if (this->CameraMain == nullptr) {
        return;
    }

    if (this->CameraMain->GetFollowYDirection()) {
        this->CameraMain->SetFollowYDirection(false);
    } else {
        this->CameraMain->SetFollowYDirection(true);
    }
}

void Engine::RandomMaterialsTest() {
    srand(static_cast<unsigned int>(time(nullptr)));
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

    for (int i = 0; i < this->EngineMapManager.GetActiveMap()->GetObjectCount(); i++) {
        this->EngineMapManager.GetActiveMap()->GetObject(i)->SetMaterial(randomMaterial());
    }
}

void Engine::RequestMapChange(int index) {
    this->EngineMapManager.ChangeMap(index);
    std::cout << "Map changed to " << this->EngineMapManager.GetActiveMap()->GetName() << std::endl;
}

std::shared_ptr<ShaderHandler> &Engine::SelectShader(const std::string &name) {
    for (auto &shader: this->Shaders) {
        if (shader->Name == name) {
            return shader;
        }
    }
    std::cerr << "ERROR: Engine: Shader name \"" << name << "\" not found. Returning any shader." << std::endl;

    if (this->Shaders.empty()) {
        std::cerr << "FATAL: Engine: No shaders available." << std::endl;
        throw std::runtime_error("No shaders available.");
    }

    return this->Shaders.at(0);
}





