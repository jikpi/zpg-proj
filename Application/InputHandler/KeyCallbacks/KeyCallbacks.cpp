//
// Created by KOP0269 on 10/6/23.
//

#include <cstdio>
#include "KeyCallbacks.h"

std::weak_ptr<MovesetInputManager> KeyCallbacks::MovesetManager;

std::weak_ptr<Engine> KeyCallbacks::Engines;
double KeyCallbacks::LastX = 0;
double KeyCallbacks::LastY = 0;
bool KeyCallbacks::FirstInput = true;

void KeyCallbacks::error_callback(int error, const char *description) {
    fputs(description, stderr);
}

void KeyCallbacks::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

//    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

    //Camera toggle
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        KeyCallbacks::Engines.lock()->ToggleCameraLock();
    }

    //Camera movement
    if (!MovesetManager.expired()) {
        auto moveset = MovesetManager.lock();
        moveset->CallbackKey(key, scancode, action, mods);
    }

    //Camera perspective
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        KeyCallbacks::Engines.lock()->ToggleCameraPerspective();
    }

    //Camera Y direction
    if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
        KeyCallbacks::Engines.lock()->ToggleCameraYDirection();
    }

    //Map change
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_1:
                if (!Engines.expired()) {
                    auto engine = Engines.lock();
                    engine->RequestMapChange(0);
                }
                break;
            case GLFW_KEY_2:
                if (!Engines.expired()) {
                    auto engine = Engines.lock();
                    engine->RequestMapChange(1);
                }
                break;
            case GLFW_KEY_3:
                if (!Engines.expired()) {
                    auto engine = Engines.lock();
                    engine->RequestMapChange(2);
                }
                break;
            case GLFW_KEY_4:
                if (!Engines.expired()) {
                    auto engine = Engines.lock();
                    engine->RequestMapChange(3);
                }
                break;
            case GLFW_KEY_5:
                if (!Engines.expired()) {
                    auto engine = Engines.lock();
                    engine->RequestMapChange(4);
                }
                break;
            case GLFW_KEY_6:
                if (!Engines.expired()) {
                    auto engine = Engines.lock();
                    engine->RequestMapChange(5);
                }
                break;
            case GLFW_KEY_7:
                if (!Engines.expired()) {
                    auto engine = Engines.lock();
                    engine->RequestMapChange(6);
                }
                break;
            case GLFW_KEY_8:
                if (!Engines.expired()) {
                    auto engine = Engines.lock();
                    engine->RequestMapChange(7);
                }
                break;
            case GLFW_KEY_9:
                if (!Engines.expired()) {
                    auto engine = Engines.lock();
                    engine->RequestMapChange(8);
                }
                break;
            default:
                break;

        }
    }

    //Random materials
    if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        if (!Engines.expired()) {
            auto engine = Engines.lock();
            engine->RandomMaterialsTest();
        }
    }


}

void KeyCallbacks::window_focus_callback(GLFWwindow *window, int focused) { printf("window_focus_callback \n"); }

void KeyCallbacks::window_iconify_callback(GLFWwindow *window, int iconified) {
    printf("window_iconify_callback \n");
}

void KeyCallbacks::window_size_callback(GLFWwindow *window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);

    if (!Engines.expired()) {
        auto engine = Engines.lock();
        engine->NotifyWindowResize(width, height);
    }
}

void KeyCallbacks::cursor_callback(GLFWwindow *window, double x, double y) {
    //printf("cursor_callback \n");

    if (FirstInput) {
        LastX = x;
        LastY = y;
        FirstInput = false;
    }

    double xChanged = x - LastX;
    double yChanged = LastY - y;

    LastX = x;
    LastY = y;

    const float sensitivity = 0.05;
    xChanged *= sensitivity;
    yChanged *= sensitivity;

    std::shared_ptr<Engine> engine = Engines.lock();


    engine->CameraLookHorizontal(xChanged);
    engine->CameraLookVertical(yChanged);

    engine->SaveCursorCoords(x, y);
}

void KeyCallbacks::button_callback(GLFWwindow *window, int button, int action, int mode) {
    if (action == GLFW_PRESS)
        printf("button_callback [%d,%d,%d]\n", button, action, mode);

    if (!Engines.expired()) {
        auto engine = Engines.lock();
        engine->CursorClick(button, action, mode);
    }


}