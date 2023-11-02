//
// Created by KOP0269 on 10/6/23.
//

#ifndef ZPG_TEST_KEYCALLBACKS_H
#define ZPG_TEST_KEYCALLBACKS_H

//Include glew
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include "../MovesetInputManager.h"
#include "../../Engine.h"

class KeyCallbacks {
public:
    static void error_callback(int error, const char *description);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void window_focus_callback(GLFWwindow *window, int focused);
    static void window_iconify_callback(GLFWwindow *window, int iconified);
    static void window_size_callback(GLFWwindow *window, int width, int height);
    static void cursor_callback(GLFWwindow *window, double x, double y);
    static void button_callback(GLFWwindow *window, int button, int action, int mode);

    static std::weak_ptr<MovesetInputManager> MovesetManager;

    static std::weak_ptr<Engine> Engines;
    static double LastX;
    static double LastY;
    static bool FirstInput;
};


#endif //ZPG_TEST_KEYCALLBACKS_H
