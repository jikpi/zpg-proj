//
// Created by lvi on 30.11.23.
//

#include <stdexcept>
#include <iostream>
#include "AnyGameLogic.h"

StandardisedModel *AnyGameLogic::ObjectByCursor(float xCursorCoords, float yCursorCoords, int windowHeight) {
    GLbyte color[4]{};
    GLfloat depth{};
    GLuint index{};

    auto x = static_cast<GLint>(xCursorCoords);
    auto y = static_cast<GLint>(yCursorCoords);

    // Convert from window coordinates to pixel coordinates
    int convertedY = windowHeight - y;

    glReadPixels(x, convertedY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, convertedY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, convertedY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);


    return this->Resources->GetObjectByContextID(index);
}

glm::vec3 AnyGameLogic::UnprojectCursor(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth) {
    GLfloat depth{};

    auto x = static_cast<GLint>(xCursorCoords);
    auto y = static_cast<GLint>(yCursorCoords);

    // Convert from window coordinates to pixel coordinates
    int convertedY = windowHeight - y;

    glReadPixels(x, convertedY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    //Unproject
    glm::vec3 screenX = glm::vec3(x, convertedY, depth);
    glm::vec3 unprojected = this->CameraMain->GetUnprojectedCursor(windowWidth, windowHeight, screenX);


    return unprojected;
}

void AnyGameLogic::InitializeResources(ResourcesManager *resources, Map *t_map, Camera *camera) {
    this->Resources = resources;
    this->map = t_map;
    this->CameraMain = camera;

    if (this->Resources == nullptr || this->CameraMain == nullptr) {
        throw std::runtime_error("ERROR: AnyGameLogic: A resource is null.");
    }

    if (!this->SelfCreatingMap() && this->map == nullptr) {
        throw std::runtime_error("ERROR: AnyGameLogic: Map is null.");
    }

    this->IsInitialized = true;
}

std::string AnyGameLogic::GetMapName() const {
    return this->map->GetName();
}

bool AnyGameLogic::CheckIfCanNextRender() const {
    if (!this->IsInitialized) {
        std::cerr << "ERROR: AnyGameLogic: Resources not initialized." << std::endl;
        return false;
    }

    if (!this->IsReady) {
        std::cerr << "ERROR: AnyGameLogic: Resources not ready." << std::endl;
        return false;
    }

    return true;
}

ShaderHandler *AnyGameLogic::SelectShader(std::vector<std::shared_ptr<ShaderHandler>> &shaders, const std::string &shaderName) {
    for (auto &shader: shaders) {
        if (shader->Name == shaderName) {
            return shader.get();
        }
    }
    std::cerr << "ERROR: AnyGameLogic: Shader name \"" << shaderName << "\" not found. Returning any shader." << std::endl;

    if (shaders.empty()) {
        std::cerr << "FATAL: AnyGameLogic: No shaders available." << std::endl;
        throw std::runtime_error("No shaders available.");
    }

    return shaders.at(0).get();
}

StandardisedModel *AnyGameLogic::ObjectByCenter(int windowHeight, int windowWidth) {
    GLbyte color[4]{};
    GLfloat depth{};
    GLuint index{};

    // Center coordinates
    auto x = windowWidth / 2;
    auto y = windowHeight / 2;

    // Convert from window coordinates to pixel coordinates
    int convertedY = windowHeight - y;

    glReadPixels(x, convertedY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, convertedY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, convertedY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    return this->Resources->GetObjectByContextID(index);
}

glm::vec3 AnyGameLogic::UnprojectCenter(int windowHeight, int windowWidth) {
    GLfloat depth{};

    // Center coordinates
    auto x = windowWidth / 2;
    auto y = windowHeight / 2;

    // Convert from window coordinates to pixel coordinates
    int convertedY = windowHeight - y;

    glReadPixels(x, convertedY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

    // Unproject
    glm::vec3 screenX = glm::vec3(x, convertedY, depth);
    glm::vec3 unprojected = this->CameraMain->GetUnprojectedCursor(windowWidth, windowHeight, screenX);

    return unprojected;
}
