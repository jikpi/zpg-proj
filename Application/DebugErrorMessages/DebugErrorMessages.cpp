//
// Created by KOP0269 on 10/7/23.
//

#include <GL/glew.h>
#include <iostream>
#include "DebugErrorMessages.h"

void DebugErrorMessages::PrintGLErrors(const char *desc) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        const char *errorString;
        switch (error) {
            case GL_INVALID_ENUM:
                errorString = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                errorString = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                errorString = "GL_INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                errorString = "GL_STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                errorString = "GL_STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                errorString = "GL_OUT_OF_MEMORY";
                break;
            default:
                errorString = "Unknown error";
                break;
        }
        std::cerr << "### OpenGL error: \"" << errorString << "\" for " << desc << std::endl;
    }
}

void
DebugErrorMessages::ErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                                  const void *userParam) {
    std::string sourceInfo;
    switch (source) {
        case GL_DEBUG_SOURCE_API:
            sourceInfo = "API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            sourceInfo = "WINDOW_SYSTEM";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            sourceInfo = "SHADER_COMPILER";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            sourceInfo = "THIRD_PARTY";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            sourceInfo = "SOURCE_APPLICATION";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            sourceInfo = "SOURCE_OTHER";
            break;
        default:
            sourceInfo = "UNKNOWN ?";
    }

    std::string typeInfo;
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            typeInfo = "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeInfo = "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeInfo = "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            typeInfo = "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            typeInfo = "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_MARKER:
            typeInfo = "MARKER";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            typeInfo = "PUSH_GROUP";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            typeInfo = "POP_GROUP";
            break;
        case GL_DEBUG_TYPE_OTHER:
            typeInfo = "OTHER";
            break;
        default:
            typeInfo = "UNKNOWN ?";
    }

    std::string severityInfo;
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            severityInfo = "HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severityInfo = "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severityInfo = "LOW";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severityInfo = "NOTIFICATION";
            return; // Notifications disabled
        default:
            severityInfo = "UNKNOWN ?";
    }

    std::cerr << "## OpenGL Message (" << id << ") ##" << std::endl
              << "# SOURCE:   " << sourceInfo << std::endl
              << "# TYPE:     " << typeInfo << std::endl
              << "# SEVERITY: " << severityInfo << std::endl
              << "# MESSAGE:  " << message << std::endl
              << std::endl;
}
