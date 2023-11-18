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

//Map creator
#include "ObjectsManager/Map/PremadeMaps/MapCreator.h"


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
    Window = glfwCreateWindow(1700, 900, "ZPG KOP0269", nullptr, nullptr);
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
    glDepthFunc(GL_LEQUAL); //GL_LESS

    glfwGetFramebufferSize(Window, &Width, &Height);
    Ratio = Width / (float) Height;
    glViewport(0, 0, Width, Height);


    //Camera lock
    glfwSetCursorPosCallback(Window, KeyCallbacks::cursor_callback);
//    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Map
    this->ResourceManager.Initialize(false);

    //Camera
    this->CameraMain = std::make_shared<Camera>();
    this->CameraMain->SetAspectRatio(this->Ratio);

    //Shaders
    LoadAllShaders();


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
            this->ResourceManager.GetLightOnMap("4 spheres", 0));

    std::shared_ptr<LightSpot> manyObjectsFlash = std::dynamic_pointer_cast<LightSpot>(
            this->ResourceManager.GetLightOnMap("Overworld", 0));

    this->CameraMain->MoveForwardBackward(0);
    this->ResourceManager.ChangeMap(0);
    this->ResourceManager.ForceRefreshMaps();
    while (!glfwWindowShouldClose(Window)) {
        //Update camera position
        UpdateMoveset();

        //Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //animate mercury
        ResourceManager.GetObjectOnMap("Solar system", "Mercury")->DoTransf();
        //animate venus
        ResourceManager.GetObjectOnMap("Solar system", "Venus")->DoTransf();
        //animate earth
        ResourceManager.GetObjectOnMap("Solar system", "Earth")->DoTransf();
        //animate mars
        ResourceManager.GetObjectOnMap("Solar system", "Mars")->DoTransf();


        angle += angleIncrement;
        if (angle > 2 * glm::pi<float>()) {
            angle -= 2 * glm::pi<float>();
        }

        float x = radius * cos(angle);
        float z = radius * sin(angle);

        spheresSpotLight->SetDirection(glm::vec3(x, 0.0f, z));

        //set many objects spot light to camera location and target
        manyObjectsFlash->SetPosition(this->CameraMain->GetLocation());
        manyObjectsFlash->SetDirection(this->CameraMain->GetTarget() - this->CameraMain->GetLocation());
        ResourceManager.ForceRefreshLightsOnCurrentMap();

        ////Render skybox
        if (ResourceManager.GetActiveMap()->Skybox != nullptr) {
            ShaderHandler *skyboxShader = ResourceManager.GetActiveMap()->Skybox->GetShaderProgram();
            glDepthMask(GL_FALSE);
            glDepthFunc(GL_LEQUAL);
            glDisable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
            skyboxShader->UseProgram();
            skyboxShader->RequestRender(*ResourceManager.GetActiveMap()->Skybox);
            ResourceManager.GetActiveMap()->Skybox->BindVertexArray();
            glDrawArrays(GL_TRIANGLES, 0, ResourceManager.GetActiveMap()->Skybox->GetRenderingSize());
            glDepthMask(GL_TRUE);
            glDepthFunc(GL_LESS);
            glEnable(GL_CULL_FACE);
            ShaderHandler::StopProgram();
        }

        ////Render each shader
        for (auto &set: this->ResourceManager.ShaderLinker) {
            set->Shader->UseProgram();

            //Render objects for chosen shader
            for (auto &object: set->Objects) {
                set->Shader->RequestRender(*object);
                object->BindVertexArray();
                glDrawArrays(GL_TRIANGLES, 0, object->GetRenderingSize());
            }

            ShaderHandler::StopProgram();
        }

        glfwPollEvents();
        glfwSwapBuffers(Window);
    }

}

void Engine::KillWindow() const {
    glfwDestroyWindow(Window);
}

void Engine::TestLaunch() {
    MapCreator::FourSpheres("4 spheres", this->Shaders, this->ResourceManager);
    MapCreator::SolarSystem("Solar system", this->Shaders, this->ResourceManager);
    MapCreator::Overworld("Overworld", this->Shaders, this->ResourceManager);

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

    for (int i = 0; i < this->ResourceManager.GetActiveMap()->GetObjectCount(); i++) {
        this->ResourceManager.GetActiveMap()->GetObject(i)->SetMaterial(randomMaterial());
    }
}

void Engine::RequestMapChange(int index) {
    this->ResourceManager.ChangeMap(index);
    std::cout << "Map changed to " << this->ResourceManager.GetActiveMap()->GetName() << std::endl;
}

void Engine::RequestMapChange(const std::string &name) {
    this->ResourceManager.ChangeMap(name);
    std::cout << "Map changed to " << this->ResourceManager.GetActiveMap()->GetName() << std::endl;
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

void Engine::LoadAllShaders() {
    this->Shaders.push_back(ShaderHandlerFactory::Phong());
    this->Shaders.push_back(ShaderHandlerFactory::Lambert());
    this->Shaders.push_back(ShaderHandlerFactory::ConstantColored());
    this->Shaders.push_back(ShaderHandlerFactory::BlinnPhong());
    this->Shaders.push_back(ShaderHandlerFactory::PhongTexture());
    this->Shaders.push_back(ShaderHandlerFactory::Skybox());


    if (this->CameraMain != nullptr) {
        for (auto &shader: this->Shaders) {
            this->CameraMain->RegisterCameraObserver(shader);
        }
    } else {
        std::cerr << "FATAL: Engine: No camera available." << std::endl;
        throw std::runtime_error("No camera available.");
    }


    this->ResourceManager.SetFallbackShader(SelectShader("Phong"));
}





