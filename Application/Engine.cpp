//
// Created by KOP0269 on 25.9.23.
//

#include "Engine.h"
#include "../Model/Factory/ModelFactory.h"
#include "DebugErrorMessages/DebugErrorMessages.h"

#include <cmath>
#include "InputHandler/KeyCallbacks/KeyCallbacks.h"

//Shaders
#include "../Shaders/ShaderProgram/ShaderHandlerFactory/ShaderHandlerFactory.h"

//Models
#include "../Shaders/Lighting/LightSpot.h"

//Map creator
#include "Managers/EngineResources/PremadeMaps/MapCreator.h"
#include "GameLogic/Solar system/GameLogic_SolarSystem.h"


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
    Window = glfwCreateWindow(1700, 900, "CREATING WINDOW", nullptr, nullptr);
    if (!Window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowOpacity(Window, 0.5f);
    glfwSetWindowTitle(Window, "LOADING...");


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

    //Resources
    this->Resources = std::make_unique<ResourcesManager>();
    this->Resources->Initialize(false);

    //Camera
    Resources->CameraMain->SetAspectRatio(this->Ratio);

    //Shaders
    LoadAllShaders();

    //Stencil test
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


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

    if (Resources->CameraMain != nullptr) {
        Resources->CameraMain->SetAspectRatio(this->Ratio);
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

void Engine::TestLaunch() {
    MapCreator::FourSpheres("4 spheres", this->Shaders, this->Resources.get());

    MapCreator::SolarSystem(this->Shaders, this->Resources.get());
//    std::unique_ptr<AnyGameLogic> solarsystemLogic = std::make_unique<GameLogic_SolarSystem>();
//    solarsystemLogic->InitializeResources(this->Resources.get(), this->CameraMain.get());

    MapCreator::Overworld("Overworld", this->Shaders, this->Resources.get());
}

void Engine::Run() {
    if (Resources->CameraMain == nullptr) {
        std::cerr << "FATAL: Engine: No camera available." << std::endl;
        throw std::runtime_error("No camera available.");
    }

    //Restore window visibility
    glfwSetWindowOpacity(Window, 1.0f);
    glfwSetWindowTitle(Window, "ZPG KOP0269");

    this->SetCameraLock(true);
    DebugErrorMessages::PrintGLErrors("Before run errors");


    float radius = 1.0f;
    float angle = 0.0f;
    float angleIncrement = glm::radians(1.0f);

    std::shared_ptr<LightSpot> manyObjectsFlash = std::dynamic_pointer_cast<LightSpot>(
            this->Resources->GetLightOnMap("Overworld", 0));

    std::shared_ptr<StandardisedModel> movingModel = this->Resources->GetObjectOnMap(0, 0);


    Resources->CameraMain->MoveForwardBackward(0);
    this->Resources->ChangeMap(0);
    this->Resources->ForceRefreshMaps();
    while (!glfwWindowShouldClose(Window)) {
        //Update camera position
        UpdateMoveset();

        //Decrease map change lock
        if (this->MapChangeFrameLock > 0) {
            this->MapChangeFrameLock--;
        }

        //Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//        angle += angleIncrement;
//        if (angle > 2 * glm::pi<float>()) {
//            angle -= 2 * glm::pi<float>();
//        }
//
//        float x = radius * cos(angle);
//        float z = radius * sin(angle);
//
//        spheresSpotLight->SetDirection(glm::vec3(x, 0.0f, z));

        //set many objects spot light to camera location and target
        manyObjectsFlash->SetPosition(Resources->CameraMain->GetLocation());
        manyObjectsFlash->SetDirection(Resources->CameraMain->GetTarget() - Resources->CameraMain->GetLocation());
        Resources->ForceRefreshLightsOnCurrentMap();

        ////Render skybox
        if (Resources->GetActiveMap()->GetSkybox() != nullptr) {
            ShaderHandler *skyboxShader = Resources->GetActiveMap()->GetSkybox()->GetShaderProgram();
            glDepthMask(GL_FALSE);
            glDepthFunc(GL_LEQUAL);
            glDisable(GL_CULL_FACE);
            skyboxShader->UseProgram();
            skyboxShader->RequestRender(*Resources->GetActiveMap()->GetSkybox());
            Resources->GetActiveMap()->GetSkybox()->BindVertexArray();
            glDrawArrays(GL_TRIANGLES, 0, Resources->GetActiveMap()->GetSkybox()->GetRenderingSize());

            glDepthMask(GL_TRUE);
            glDepthFunc(GL_LESS);
            glEnable(GL_CULL_FACE);
            ShaderHandler::StopProgram();
        }

        ////Render each shader
        for (auto &set: this->Resources->ShaderLinker) {
            set->Shader->UseProgram();

            //Render objects for chosen shader
            for (auto &object: set->Objects) {
                object->DoAnyAnimation(0);
                set->Shader->RequestRender(*object);
                object->BindVertexArray();

                //Set stencil
                if (object->DesiredContextID != DEF_CONTEXT_ERROR_ID) {
                    glStencilFunc(GL_ALWAYS, object->GetContextID(), 0xFF);
                }


                glDrawArrays(GL_TRIANGLES, 0, object->GetRenderingSize());

                //Render inner objects
                if (!object->ChildObjects.empty()) {
                    object->SetChildrenTransformations();
                    for (auto &innerObject: object->ChildObjects) {
                        set->Shader->RequestRender(*innerObject);
                        innerObject->BindVertexArray();
                        glDrawArrays(GL_TRIANGLES, 0, innerObject->GetRenderingSize());
                    }
                }
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

void Engine::CameraLookHorizontal(double x) {
    if (Resources->CameraMain != nullptr) {
        Resources->CameraMain->LookSphericalSide(x);
    }
}

void Engine::CameraLookVertical(double y) {
    if (Resources->CameraMain != nullptr) {
        Resources->CameraMain->LookSphericalVertical(y);
    }
}

void Engine::UpdateMoveset() {
    if (this->MovesetManager == nullptr) {
        return;
    }

    if (this->MovesetManager->IsStandStill()) {
        return;
    }

    if (Resources->CameraMain == nullptr) {
        return;
    }


    float reading;
    reading = this->MovesetManager->ReadForward();
    if (reading != 0) {
        Resources->CameraMain->MoveForwardBackward(reading);
    }

    reading = this->MovesetManager->ReadSide();
    if (reading != 0) {
        Resources->CameraMain->MoveSideToSide(reading);
    }

    reading = this->MovesetManager->ReadVertical();
    if (reading != 0) {
        Resources->CameraMain->MoveUpDown(reading);
    }
}

void Engine::SetCameraLock(bool lock) {

    if (Resources->CameraMain == nullptr) {
        return;
    }

    if (lock) {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        Resources->CameraMain->UnlockSet(true);
    } else {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        Resources->CameraMain->UnlockSet(false);
    }
}

void Engine::ToggleCameraLock() {
    if (Resources->CameraMain->UnlockState()) {
        this->SetCameraLock(false);
    } else {
        this->SetCameraLock(true);
    }
}

void Engine::AddShader(const std::shared_ptr<ShaderHandler> &shader) {
    this->Shaders.push_back(shader);
}

void Engine::ToggleCameraPerspective() {
    if (Resources->CameraMain == nullptr) {
        return;
    }

    if (Resources->CameraMain->GetPerspectiveProjection()) {
        Resources->CameraMain->SetPerspectiveProjection(false);
    } else {
        Resources->CameraMain->SetPerspectiveProjection(true);
    }
}

void Engine::ToggleCameraYDirection() {
    if (Resources->CameraMain == nullptr) {
        return;
    }

    if (Resources->CameraMain->GetFollowYDirection()) {
        Resources->CameraMain->SetFollowYDirection(false);
    } else {
        Resources->CameraMain->SetFollowYDirection(true);
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

    for (int i = 0; i < this->Resources->GetActiveMap()->GetObjectCount(); i++) {
        this->Resources->GetActiveMap()->GetObject(i)->SetMaterial(randomMaterial());
    }
}

void Engine::RequestMapChange(int index) {
    if (this->MapChangeFrameLock > 0) {
        return;
    }

    MapChangeFrameLock = DEF_MAP_CHANGE_TIMEOUT;
    this->Resources->ChangeMap(index);
    std::cout << "Map changed to " << this->Resources->GetActiveMap()->GetName() << std::endl;
}

void Engine::RequestMapChange(const std::string &name) {
    if (this->MapChangeFrameLock > 0) {
        return;
    }

    MapChangeFrameLock = DEF_MAP_CHANGE_TIMEOUT;
    this->Resources->ChangeMap(name);
    std::cout << "Map changed to " << this->Resources->GetActiveMap()->GetName() << std::endl;
}

void Engine::LoadAllShaders() {
    this->Shaders.push_back(ShaderHandlerFactory::Phong());
    this->Shaders.push_back(ShaderHandlerFactory::Lambert());
    this->Shaders.push_back(ShaderHandlerFactory::ConstantColored());
    this->Shaders.push_back(ShaderHandlerFactory::BlinnPhong());
    this->Shaders.push_back(ShaderHandlerFactory::PhongTexture());
    this->Shaders.push_back(ShaderHandlerFactory::Skybox());


    if (Resources->CameraMain != nullptr) {
        for (auto &shader: this->Shaders) {
            Resources->CameraMain->RegisterCameraObserver(shader);
        }
    } else {
        std::cerr << "FATAL: Engine: No camera available." << std::endl;
        throw std::runtime_error("No camera available.");
    }


    this->Resources->SetFallbackShader(this->Shaders.at(0));
}

void Engine::SaveCursorCoords(float x, float y) {
    this->SavedCursorXCoord = x;
    this->SavedCursorYCoord = y;
}

void Engine::CursorClick(int button, int action, int mode) {
    Resources->MouseCursorClickEvent(this->SavedCursorXCoord,
                                     this->SavedCursorYCoord,
                                     this->Height,
                                     this->Width, button,
                                     action, mode);

//    GLbyte color[4]{};
//    GLfloat depth{};
//    GLuint index{};
//
//    auto x = static_cast<GLint>(this->SavedCursorXCoord);
//    auto y = static_cast<GLint>(this->SavedCursorYCoord);
//
//    // Convert from window coordinates to pixel coordinates
//    int convertedY = this->Height - y;
//
//    glReadPixels(x, convertedY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
//    glReadPixels(x, convertedY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
//    glReadPixels(x, convertedY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
//
//    std::cout << "stencil index " << index
//              << ", clicked on pixel " << x << ", " << y
//              << ", color " << (int) color[0] << ", "
//              << (int) color[1] << ", "
//              << (int) color[2] << ", "
//              << (int) color[3]
//              << ", depth " << depth
//              << std::endl;
//
//
//    if (button == 0 && action == 1 && mode == 0) {
//
//
//        srand(static_cast<unsigned int>(time(nullptr)));
//        auto randomMaterial = []() -> Material {
//            Material material;
//            material.AmbientColor = glm::vec3(0.1f, 0.1f, 0.1f);
//            material.DiffuseColor = glm::vec3((float) rand() / RAND_MAX, (float) rand() / RAND_MAX,
//                                              (float) rand() / RAND_MAX);
//            material.SpecularColor = glm::vec3((float) rand() / RAND_MAX, (float) rand() / RAND_MAX,
//                                               (float) rand() / RAND_MAX);
//            material.ShineValue = (float) rand() / RAND_MAX * 245 + 10;
//            return material;
//        };
//
//        StandardisedModel *pointedObj = this->Resources->GetObjectByContextID(index);
//        if (pointedObj != nullptr) {
//            pointedObj->SetMaterial(randomMaterial());
//        }
//    }
//
//    if (button == 1 && action == 1 && mode == 0) {
//
//
//        //Unproject
//        glm::vec3 screenX = glm::vec3(x, convertedY, depth);
//        glm::vec3 unprojected = this->CameraMain->GetUnprojectedCursor(this->Width, this->Height, screenX);
//
//        std::cout << "Unprojected: " << unprojected.x << ", " << unprojected.y << ", " << unprojected.z << std::endl;
//        std::cout << "-------" << std::endl;
//
////        Add model at the location
//        std::shared_ptr<StandardisedModel> spawnedModel = Resources->ModelObjectController.UseAny("Lesson/zombie.obj", "Zombie");
//        spawnedModel->InsertTransfMove(glm::vec3(unprojected.x, unprojected.y, unprojected.z)).ConsolidateTransf();
//
//        spawnedModel->SetDefaultMaterial();
//        Resources->AddObjectToCurrentMap(spawnedModel);
//
//    }
//

}

void Engine::KeyPress(int key, int scancode, int action, int mods) {
    Resources->KeyPressEvent(key, scancode, action, mods);
}
