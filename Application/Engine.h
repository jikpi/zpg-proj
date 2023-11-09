//
// Created by KOP0269 on 25.9.23.
//

#ifndef ZPG_TEST_ENGINE_H
#define ZPG_TEST_ENGINE_H

//Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include "../Shaders/ShaderProgram/ShaderHandler.h"
#include "ObjectsManager/Map/Map.h"
#include "InputHandler/MovesetInputManager.h"
#include "../Shaders/Camera/Camera.h"
#include "ObjectsManager/ShaderLinking/MapToShaderLinker.h"
#include "ObjectsManager/Map/MapManager.h"

class Engine : public std::enable_shared_from_this<Engine> {
private:
    void InitializeInputHandling();

    GLFWwindow *Window{};
    int Width{};
    int Height{};
    float Ratio{};

    std::vector<std::shared_ptr<ShaderHandler>> Shaders;
    MapManager ResourceManager;
    TextureController ObjectTextureController;
    std::shared_ptr<ShaderHandler> & SelectShader(const std::string& name);

    std::shared_ptr<Camera> CameraMain;

    std::shared_ptr<MovesetInputManager> MovesetManager;

    void UpdateMoveset();

public:
    explicit Engine();

    void Initialize();
    static void PrintVersionInfo();
    void Run();
    void KillWindow() const;

    void NotifyWindowResize(int newWidth, int newHeight);
    void CameraLookHorizontal(double x);
    void CameraLookVertical(double y);
    void SetCameraLock(bool lock);
    void ToggleCameraLock();
    void ToggleCameraPerspective();
    void ToggleCameraYDirection();
    void RequestMapChange(int index);
    void RequestMapChange(const std::string &name);


    void AddShader(const std::shared_ptr<ShaderHandler> &shader);

    void TestLaunch();
    void RandomMaterialsTest();
};


#endif //ZPG_TEST_ENGINE_H
