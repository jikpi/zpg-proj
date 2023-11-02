//
// Created by KOP0269 on 10/7/23.
//

#ifndef ZPG_TEST_DEBUGERRORMESSAGES_H
#define ZPG_TEST_DEBUGERRORMESSAGES_H

//Include glew
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

class DebugErrorMessages {
public:
    static void PrintGLErrors(const char *desc = "");
    static void APIENTRY ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                       const GLchar *message, const void *userParam);
};


#endif //ZPG_TEST_DEBUGERRORMESSAGES_H
