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

//Transformations
#include "../Transformations/Composite/Factory/TransformationFactory.h"

//Models
#include "../ExtResources/LessonResources/InclLessonModels.h"
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

    //Map
    this->ResourceManager.Initialize(false);

    //Camera
    this->CameraMain = std::make_unique<Camera>();
    this->CameraMain->SetAspectRatio(this->Ratio);

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

void Engine::TestLaunch() {
    MapCreator::FourSpheres("4 spheres", this->Shaders, this->ResourceManager);
    MapCreator::SolarSystem("Solar system", this->Shaders, this->ResourceManager);
    MapCreator::Overworld("Overworld", this->Shaders, this->ResourceManager);
}

// Function to calculate a point on a Bezier curve defined by four control points
glm::vec3 CalculateBezierPoint(float t, const glm::vec3 &p0, const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3) {
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    glm::vec3 p = uuu * p0; //first term
    p += 3 * uu * t * p1; //second term
    p += 3 * u * tt * p2; //third term
    p += ttt * p3; //fourth term

    return p;
}

void Engine::Run() {
    if (this->CameraMain == nullptr) {
        std::cerr << "FATAL: Engine: No camera available." << std::endl;
        throw std::runtime_error("No camera available.");
    }

    //Restore window visibility
    glfwSetWindowOpacity(Window, 1.0f);
    glfwSetWindowTitle(Window, "ZPG KOP0269");

    this->SetCameraLock(true);
    DebugErrorMessages::PrintGLErrors("Before run errors");


    ////Bezier points
    std::vector<glm::vec3> controlPoints = {
            glm::vec3(0, 0, 0),     // First segment
            glm::vec3(2, 2, 0),
            glm::vec3(-4, 4, 0),
            glm::vec3(6, 0, 0),     // Second segment starts
            glm::vec3(8, -10, 0),
            glm::vec3(10, 4, 0),
            glm::vec3(12, 0, 0),    // Third segment starts
            glm::vec3(14, 20, 20),  // New points for the third segment
            glm::vec3(16, 25, 15),
            glm::vec3(18, 15, 10),
            glm::vec3(20, 10, 5)
    };


    float t = 0;
    float tchange = 0.001f;


    float radius = 1.0f;
    float angle = 0.0f;
    float angleIncrement = glm::radians(1.0f);

    std::shared_ptr<LightSpot> spheresSpotLight = std::dynamic_pointer_cast<LightSpot>(
            this->ResourceManager.GetLightOnMap("4 spheres", 0));

    std::shared_ptr<LightSpot> manyObjectsFlash = std::dynamic_pointer_cast<LightSpot>(
            this->ResourceManager.GetLightOnMap("Overworld", 0));

    std::shared_ptr<StandardisedModel> movingModel = this->ResourceManager.GetObjectOnMap(0, 0);


    this->CameraMain->MoveForwardBackward(0);
    this->ResourceManager.ChangeMap(0);
    this->ResourceManager.ForceRefreshMaps();
    while (!glfwWindowShouldClose(Window)) {
        //Update camera position
        UpdateMoveset();


        ////Bezier
        // Determine which segment of the curve t is in
        int numSegments = (controlPoints.size() - 1) / 3;
        int currentSegment = std::min(static_cast<int>(t * numSegments), numSegments - 1);

        // Calculate the local t for the segment
        float localT = (t * numSegments) - currentSegment;

        // Calculate the point on the current Bezier segment
        glm::vec3 p0 = controlPoints[currentSegment * 3];
        glm::vec3 p1 = controlPoints[currentSegment * 3 + 1];
        glm::vec3 p2 = controlPoints[currentSegment * 3 + 2];
        glm::vec3 p3 = controlPoints[currentSegment * 3 + 3];

        glm::vec3 p = CalculateBezierPoint(localT, p0, p1, p2, p3);

        // Bezier test
        std::cout << "t = " << t << " P=[ " << p[0] << ", " << p[1] << ", " << p[2] << "]" << std::endl;
        t += tchange;
        if (t >= 1.0f || t <= 0.0f) {
            tchange = -tchange;
        }

        // Apply transformation to the moving model based on the Bezier curve point
        movingModel->ClearTransf();
        movingModel->ResetTransf();
        movingModel->InsertTransfMove(glm::vec3(p[0], p[1], p[2]));



        //Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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
        if (ResourceManager.GetActiveMap()->GetSkybox() != nullptr) {
            ShaderHandler *skyboxShader = ResourceManager.GetActiveMap()->GetSkybox()->GetShaderProgram();
            glDepthMask(GL_FALSE);
            glDepthFunc(GL_LEQUAL);
            glDisable(GL_CULL_FACE);
            skyboxShader->UseProgram();
            skyboxShader->RequestRender(*ResourceManager.GetActiveMap()->GetSkybox());
            ResourceManager.GetActiveMap()->GetSkybox()->BindVertexArray();
            glDrawArrays(GL_TRIANGLES, 0, ResourceManager.GetActiveMap()->GetSkybox()->GetRenderingSize());

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
                object->DoTransf();
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

    if (this->CameraMain == nullptr) {
        return;
    }

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


    this->ResourceManager.SetFallbackShader(this->Shaders.at(0));
}

void Engine::SaveCursorCoords(float x, float y) {
    this->SavedCursorXCoord = x;
    this->SavedCursorYCoord = y;
}

void Engine::CursorClick(int button, int action, int mode) {
    GLbyte color[4]{};
    GLfloat depth{};
    GLuint index{};

    auto x = static_cast<GLint>(this->SavedCursorXCoord);
    auto y = static_cast<GLint>(this->SavedCursorYCoord);

    // Convert from window coordinates to pixel coordinates
    int convertedY = this->Height - y;

    glReadPixels(x, convertedY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, convertedY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, convertedY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    std::cout << "stencil index " << index
              << ", clicked on pixel " << x << ", " << y
              << ", color " << (int) color[0] << ", "
              << (int) color[1] << ", "
              << (int) color[2] << ", "
              << (int) color[3]
              << ", depth " << depth
              << std::endl;


    if (button == 0 && action == 1 && mode == 0) {


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

        StandardisedModel *pointedObj = this->ResourceManager.GetObjectByContextID(index);
        if (pointedObj != nullptr) {
            pointedObj->SetMaterial(randomMaterial());
        }
    }

    if (button == 1 && action == 1 && mode == 0) {


        //Unproject
        glm::vec3 screenX = glm::vec3(x, convertedY, depth);
        glm::vec3 unprojected = this->CameraMain->GetUnprojectedCursor(this->Width, this->Height, screenX);

        std::cout << "Unprojected: " << unprojected.x << ", " << unprojected.y << ", " << unprojected.z << std::endl;
        std::cout << "-------" << std::endl;

//        Add model at the location
        std::shared_ptr<StandardisedModel> spawnedModel = ResourceManager.ModelObjectController.UseAny("Lesson/zombie.obj", "Zombie");
        spawnedModel->InsertTransfMove(glm::vec3(unprojected.x, unprojected.y, unprojected.z)).ConsolidateTransf();

        spawnedModel->SetDefaultMaterial();
        ResourceManager.AddObjectToCurrentMap(spawnedModel);

    }


}