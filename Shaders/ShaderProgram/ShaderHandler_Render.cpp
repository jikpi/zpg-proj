//
// Created by lvi on 23.11.23.
//

#include <iostream>
#include "ShaderHandler.h"
#include "../Lighting/LightSpot.h"
#include "../Lighting/LightDirectional.h"

void ShaderHandler::RenderBase(const glm::mat4 &modelMatrix) {
    SendToShader(ModelMatrixLocation, modelMatrix);
    SendToShader(ViewMatrixLocation, this->ViewMatrix);
    SendToShader(ProjectionMatrixLocation, this->ProjectionMatrix);
}

void ShaderHandler::RenderNormalMatrix(const glm::mat3 &normalMatrix) const {
    // Normal matrix calculated only once, and after all transformations were applied, if any were used / added.
    SendToShader(NormalMatrixLocation, normalMatrix);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-static-cast-downcast"

void ShaderHandler::RenderLightsArray(
        const std::shared_ptr<std::vector<std::shared_ptr<RenderableLight>>> &lightsVector) const {

    int pointLightsCount = 0;
    int directionalLightsCount = 0;
    int spotLightsCount = 0;
    for (auto &i: *lightsVector) {
        switch (i->GetType()) {
            case LIGHT_TYPE_POINT: {
                const auto *light = static_cast<const LightPoint *>(i.get());

                if (pointLightsCount >= LightsArrayPoint_UniformLocation.size()) {
                    std::cerr << "SHADER ERROR: POINT LIGHTS ARRAY SIZE IS SMALLER THAN LIGHTS VECTOR SIZE"
                              << std::endl;
                    this->PrintName();
                    continue;
                }

                const auto &lightArrayIndexlocation = LightsArrayPoint_UniformLocation.at(
                        pointLightsCount++);

                SendToShader(lightArrayIndexlocation.position, light->GetPosition());
                SendToShader(lightArrayIndexlocation.color, light->GetColor());
                SendToShader(lightArrayIndexlocation.intensity, light->GetIntensity());
                SendToShader(lightArrayIndexlocation.constant, light->GetConstant());
                SendToShader(lightArrayIndexlocation.linear, light->GetLinear());
                SendToShader(lightArrayIndexlocation.quadratic, light->GetQuadratic());
                break;
            }
            case LIGHT_TYPE_DIRECTIONAL: {
                const auto *light = static_cast<const LightDirectional *>(i.get());

                if (directionalLightsCount >= LightsArrayDirectional_UniformLocation.size()) {
                    std::cerr
                            << "SHADER ERROR: DIRECTIONAL LIGHTS ARRAY SIZE IS SMALLER THAN LIGHTS VECTOR SIZE"
                            << std::endl;
                    this->PrintName();
                    continue;
                }

                const auto &lightArrayIndexlocation = LightsArrayDirectional_UniformLocation.at(
                        directionalLightsCount++);

                SendToShader(lightArrayIndexlocation.direction, light->GetDirection());
                SendToShader(lightArrayIndexlocation.color, light->GetColor());
                SendToShader(lightArrayIndexlocation.intensity, light->GetIntensity());
                break;
            }
            case LIGHT_TYPE_SPOT:
                const auto *light = static_cast<const LightSpot *>(i.get());

                if (spotLightsCount >= LightsArraySpot_UniformLocation.size()) {
                    std::cerr << "SHADER ERROR: SPOT LIGHTS ARRAY SIZE IS SMALLER THAN LIGHTS VECTOR SIZE"
                              << std::endl;
                    this->PrintName();
                    continue;
                }

                const auto &lightArrayIndexlocation = LightsArraySpot_UniformLocation.at(
                        spotLightsCount++);

                SendToShader(lightArrayIndexlocation.innerCutOff, light->GetInnerCutOff());
                SendToShader(lightArrayIndexlocation.outerCutOff, light->GetOuterCutOff());
                SendToShader(lightArrayIndexlocation.direction, light->GetDirection());
                SendToShader(lightArrayIndexlocation.position, light->GetPosition());
                SendToShader(lightArrayIndexlocation.color, light->GetColor());
                SendToShader(lightArrayIndexlocation.intensity, light->GetIntensity());
                SendToShader(lightArrayIndexlocation.constant, light->GetConstant());
                SendToShader(lightArrayIndexlocation.linear, light->GetLinear());
                SendToShader(lightArrayIndexlocation.quadratic, light->GetQuadratic());
                break;
        }

    }

    SendToShader(LightsArrayPoint_SizeLocation, pointLightsCount);
    SendToShader(LightsArrayDirectional_SizeLocation, directionalLightsCount);
    SendToShader(LightsArraySpot_SizeLocation, spotLightsCount);
}

#pragma clang diagnostic pop

void ShaderHandler::RenderObjectMaterial(const Material objectMaterial) const {
    SendToShader(AmbientColorLocation, objectMaterial.AmbientColor);
    SendToShader(DiffuseColorLocation, objectMaterial.DiffuseColor);
}

void ShaderHandler::RenderPhongLight(const Material objectMaterial) const {
    SendToShader(SpecularColorLocation, objectMaterial.SpecularColor);
    SendToShader(ShineValueLocation, objectMaterial.ShineValue);
}

void ShaderHandler::RenderCameraLocation() const {
    SendToShader(CameraLocationLocation, CameraLocation);
}

void ShaderHandler::RenderBaseLightsArray() {
    if (LightsArrayPoint_SizeLocation != -2 && LightsArrayDirectional_SizeLocation != -2) {
        std::shared_ptr<std::vector<std::shared_ptr<RenderableLight>>> lightsVectorPtr = this->SelectedLightsFromMap.lock();
        if (lightsVectorPtr == nullptr) {
            std::cerr << "SHADER ERROR: LIGHTS ARRAY FROM MAP NOT LINKED" << std::endl;
            this->PrintName();
            return;
        } else {
            this->RenderLightsArray(lightsVectorPtr);
        }
    }
}

void ShaderHandler::RenderAnyTexture(Texture *texture, int target, const GLint &Location) {
    if (texture) {
        GLuint textureID = texture->GetTextureID();

        if (texture->GetTextureUnit() == -1) {
            texture->SetTextureUnit(Texture::TextureUnitCounter++);
        }

        if (texture->GetTextureUnit() >= 32) {
            std::cerr << "ERROR: Texture unit " << texture->GetTextureUnit() << " is out of range. " << std::endl;
            return;
        }

        glActiveTexture(GL_TEXTURE0 + texture->GetTextureUnit());
        glBindTexture(target, textureID);

        SendToShader(Location, texture->GetTextureUnit());
    } else {
        std::cerr << "ERROR: ShaderHandler: Texture is null" << std::endl;
    }
}


void ShaderHandler::RenderSkybox(Texture *texture) const {
    RenderAnyTexture(texture, GL_TEXTURE_CUBE_MAP, SkyboxLocation);
}

void ShaderHandler::RenderTexture(Texture *texture) const {
    RenderAnyTexture(texture, GL_TEXTURE_2D, TextureLocation);
}