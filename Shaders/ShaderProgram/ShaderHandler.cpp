//
// Created by KOP0269 on 25.9.23.
//

//Include GLM
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "ShaderHandler.h"

ShaderHandler::ShaderHandler() : ShaderBase(),
                                 ViewMatrix(glm::mat4(1.0f)),
                                 ProjectionMatrix(glm::mat4(1.0f)),
                                 HaveLightsChanged(false),
                                 CameraLocationLocation(-2),

                                 NormalMatrixLocation(-2),

                                 LightsArrayPoint_SizeLocation(-2),
                                 LightsArrayDirectional_SizeLocation(-2),
                                 LightsArraySpot_SizeLocation(-2),

                                 AmbientColorLocation(-2),
                                 DiffuseColorLocation(-2),

                                 ShineValueLocation(-2),
                                 SpecularColorLocation(-2),

                                 TextureLocation(-2),
                                 SkyboxLocation(-2) {
}


void ShaderHandler::RequestRender(RenderableObject &object) {
    glm::mat4 modelMatrix = object.GetTransf();
    RenderBase(modelMatrix);

    if (this->CameraLocationLocation != -2) {
        this->RenderCameraLocation();
    }

    if (NormalMatrixLocation != -2) {
        RenderNormalMatrix(object.GetNormalMatrix());
    }

    if (AmbientColorLocation != -2 && DiffuseColorLocation != -2) {
        this->RenderObjectMaterial(object.GetMaterial());
    }

    if (ShineValueLocation != -2 && SpecularColorLocation != -2) {
        this->RenderPhongLight(object.GetMaterial());
    }

    if (this->HaveLightsChanged) {
        this->HaveLightsChanged = false;
        this->RenderBaseLightsArray();
    }

    if (this->TextureLocation != -2) {
        this->RenderTexture(object.GetTexture());
    }

    if (this->SkyboxLocation != -2) {
        this->RenderSkybox(object.GetTexture());
    }
}


void
ShaderHandler::CameraChangedNotification(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix,
                                         const glm::vec3 &cameraLocation) {
    ViewMatrix = viewMatrix;
    ProjectionMatrix = projectionMatrix;
    CameraLocation = cameraLocation;
}

void ShaderHandler::PrintName() const {
    ShaderBase::PrintName();
}

void ShaderHandler::SetLights(std::shared_ptr<std::vector<std::shared_ptr<RenderableLight>>> &lights) {
    this->SelectedLightsFromMap = lights;
    HaveLightsChanged = true;
}

void ShaderHandler::NotifyLightsChanged() {
    HaveLightsChanged = true;
}



