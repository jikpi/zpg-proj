//
// Created by KOP0269 on 25.9.23.
//

#ifndef ZPG_TEST_ENGINE_H
#define ZPG_TEST_ENGINE_H

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include "../Shaders/ShaderProgram/ShaderHandler.h"
#include "InputHandler/MovesetInputManager.h"
#include "Managers/ShaderLinking/MapToShaderLinker.h"
#include "Managers/EngineResources/ResourcesManager.h"
#include "GameLogic/Abstract/AnyGameLogic.h"

class Engine : public std::enable_shared_from_this<Engine> {
private:
    void InitializeInputHandling();

    GLFWwindow *Window{};
    int Width{};
    int Height{};
    float Ratio{};

    std::vector<std::shared_ptr<ShaderHandler>> Shaders;
    void LoadAllShaders();

    std::unique_ptr<ResourcesManager> Resources;
    std::shared_ptr<MovesetInputManager> MovesetManager;

    void UpdateMoveset();

    float SavedCursorXCoord{};
    float SavedCursorYCoord{};

    int MapChangeFrameLock{};

public:
    explicit Engine();

    void Initialize();
    static void PrintVersionInfo();
    void Run();
    void KillWindow() const;

    void NotifyWindowResize(int newWidth, int newHeight);
    void CameraLookHorizontal(double x);
    void CameraLookVertical(double y);
    void SaveCursorCoords(float x, float y);
    void SetCameraLock(bool lock);
    void ToggleCameraLock();
    void ToggleCameraPerspective();
    void ToggleCameraYDirection();
    void RequestMapChange(int index);
    void RequestMapChange(const std::string &name);

    void CursorClick(int button, int action, int mode);
    void KeyPress(int key, int scancode, int action, int mods);


    void AddShader(const std::shared_ptr<ShaderHandler> &shader);

    void TestLaunch();
    void RandomMaterialsTest();
};


#endif //ZPG_TEST_ENGINE_H
