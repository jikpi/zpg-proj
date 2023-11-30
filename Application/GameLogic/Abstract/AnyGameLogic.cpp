//
// Created by lvi on 30.11.23.
//

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

    //Unproject
    glm::vec3 screenX = glm::vec3(x, convertedY, depth);
    glm::vec3 unprojected = this->CameraMain->GetUnprojectedCursor(windowWidth, windowHeight, screenX);


    return unprojected;
}

void AnyGameLogic::InitializeResources(ResourcesManager *resources, Map *t_map, Camera *camera) {
    this->Resources = resources;
    this->map = t_map;
    this->CameraMain = camera;
}

std::string AnyGameLogic::GetMapName() const {
    return this->map->GetName();
}
