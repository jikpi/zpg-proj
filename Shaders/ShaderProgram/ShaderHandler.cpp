//
// Created by KOP0269 on 25.9.23.
//

//Include GLM
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <iostream>
#include "ShaderHandler.h"
#include "../../Application/Configuration/AGlobalConfig.h"
#include "../Lighting/LightDirectional.h"
#include "../Lighting/LightSpot.h"

//Test soil
#include <SOIL/SOIL.h>

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

                                 SkyboxLocation(-2) {
}

ShaderHandler &ShaderHandler::SaveBaseMatrixLocations() {
    ModelMatrixLocation = GetUniformLocation(DEF_SHADER_MODEL_MATRIX_NAME);
    ViewMatrixLocation = GetUniformLocation(DEF_SHADER_VIEW_MATRIX_NAME);
    ProjectionMatrixLocation = GetUniformLocation(DEF_SHADER_PROJECTION_MATRIX_NAME);

    if ((ModelMatrixLocation == -1 || ViewMatrixLocation == -1 || ProjectionMatrixLocation == -1)) {
        std::cerr << "SHADER FATAL ERROR: A BASIC TRANSFORMATION NOT FOUND IN SHADER CODE." << std::endl;
        if (ModelMatrixLocation == -1) std::cerr << "ModelMatrix == -1" << std::endl;
        if (ViewMatrixLocation == -1) std::cerr << "ViewMatrix == -1" << std::endl;
        if (ProjectionMatrixLocation == -1) std::cerr << "ProjectionMatrix == -1" << std::endl;
        this->PrintName();
    }

    return *this;
}

ShaderHandler &ShaderHandler::SaveNormalsLocation() {
    NormalMatrixLocation = GetUniformLocation(DEF_SHADER_NORMAL_MATRIX_NAME);
    if (NormalMatrixLocation == -1) {
        std::cerr << "SHADER ERROR: NORMAL MATRIX NOT FOUND IN SHADER CODE, BUT WAS EXPECTED." << std::endl;
        this->PrintName();
    }

    return *this;
}

ShaderHandler &ShaderHandler::SaveObjectMaterialLocation() {
    AmbientColorLocation = GetUniformLocation(DEF_SHADER_MATERIAL_AMBIENTCOLOR_NAME);
    DiffuseColorLocation = GetUniformLocation(DEF_SHADER_MATERIAL_DIFFUSECOLOR_NAME);

    if (AmbientColorLocation == -1 || DiffuseColorLocation == -1) {
        std::cerr << "SHADER ERROR: MATERIAL NOT FOUND IN SHADER CODE, BUT WAS EXPECTED." << std::endl;
        if (AmbientColorLocation == -1) std::cerr << "AmbientColorLocation == -1" << std::endl;
        if (DiffuseColorLocation == -1) std::cerr << "DiffuseColorLocation == -1" << std::endl;
        this->PrintName();
    }

    return *this;
}

ShaderHandler &ShaderHandler::SaveLightingLocation() {

    //Point Lights
    this->LightsArrayPoint_SizeLocation = GetUniformLocation(DEF_SHADER_LIGHTS_POINT_ARRAY_LOCATION_SIZE_NAME);
    if (LightsArrayPoint_SizeLocation == -1) {
        std::cerr << "SHADER ERROR: *POINT* LIGHTS ARRAY NOT FOUND IN SHADER CODE, BUT WAS EXPECTED." << std::endl;
        this->PrintName();
    } else {
        std::string lightsArrayBaseName = DEF_SHADER_LIGHTS_POINT_ARRAY_LOCATION_NAME;
        for (int i = 0; i < DEF_SHADER_LIGHTS_ARRAY_LOCATION_ARRAY_SIZE; i++) {
            std::string lightName = lightsArrayBaseName + "[" + std::to_string(i) + "].";
            LightsArrayPointUniform locations{};
            locations.position = GetUniformLocation((lightName +
                                                     DEF_SHADER_LIGHTS_ARRAY_LOCATION_POSITION_NAME).c_str());
            locations.color = GetUniformLocation((lightName +
                                                  DEF_SHADER_LIGHTS_ARRAY_LOCATION_COLOR_NAME).c_str());
            locations.intensity = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_INTENSITY_NAME).c_str());
            locations.constant = GetUniformLocation((lightName +
                                                     DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_CONST_NAME).c_str());
            locations.linear = GetUniformLocation((lightName +
                                                   DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_LINEAR_NAME).c_str());
            locations.quadratic = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_QUADRATIC_NAME).c_str());

            if (locations.position == -1 || locations.color == -1 || locations.intensity == -1 ||
                locations.constant == -1 || locations.linear == -1 || locations.quadratic == -1) {
                std::cerr
                        << "SHADER ERROR: *POINT* LIGHTS ARRAY *ELEMENTS* NOT FOUND IN SHADER CODE, BUT WERE EXPECTED."
                        << std::endl;
                this->PrintName();
            } else {
                LightsArrayPoint_UniformLocation.push_back(locations);
            }
        }
    }

    //Directional Lights
    this->LightsArrayDirectional_SizeLocation = GetUniformLocation(
            DEF_SHADER_LIGHTS_DIRECTIONAL_ARRAY_LOCATION_SIZE_NAME);
    if (LightsArrayDirectional_SizeLocation == -1) {
        std::cerr << "SHADER ERROR: *DIRECTIONAL* LIGHTS ARRAY NOT FOUND IN SHADER CODE, BUT WAS EXPECTED."
                  << std::endl;
        this->PrintName();
    } else {
        std::string lightsArrayBaseName = DEF_SHADER_LIGHTS_DIRECTIONAL_ARRAY_LOCATION_NAME;
        for (int i = 0; i < DEF_SHADER_LIGHTS_ARRAY_LOCATION_ARRAY_SIZE; i++) {
            std::string lightName = lightsArrayBaseName + "[" + std::to_string(i) + "].";
            LightArrayDirectionalUniform locations{};
            locations.direction = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_DIRECTION_NAME).c_str());
            locations.color = GetUniformLocation((lightName +
                                                  DEF_SHADER_LIGHTS_ARRAY_LOCATION_COLOR_NAME).c_str());
            locations.intensity = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_INTENSITY_NAME).c_str());

            if (locations.direction == -1 || locations.color == -1 || locations.intensity == -1) {
                std::cerr
                        << "SHADER ERROR: *DIRECTIONAL* LIGHTS ARRAY *ELEMENTS* NOT FOUND IN SHADER CODE, BUT WERE EXPECTED."
                        << std::endl;
                this->PrintName();
            } else {
                LightsArrayDirectional_UniformLocation.push_back(locations);
            }
        }
    }

    //Spot lights
    this->LightsArraySpot_SizeLocation = GetUniformLocation(DEF_SHADER_LIGHTS_SPOT_ARRAY_LOCATION_SIZE_NAME);
    if (LightsArraySpot_SizeLocation == -1) {
        std::cerr << "SHADER ERROR: *SPOT* LIGHTS ARRAY NOT FOUND IN SHADER CODE, BUT WAS EXPECTED." << std::endl;
        this->PrintName();
    } else {
        std::string lightsArrayBaseName = DEF_SHADER_LIGHTS_SPOT_ARRAY_LOCATION_NAME;
        for (int i = 0; i < DEF_SHADER_LIGHTS_ARRAY_LOCATION_ARRAY_SIZE; i++) {
            std::string lightName = lightsArrayBaseName + "[" + std::to_string(i) + "].";
            LightsArraySpotUniform locations{};
            locations.innerCutOff = GetUniformLocation((lightName +
                                                        DEF_SHADER_LIGHTS_ARRAY_LOCATION_INNERCUTOFF_NAME).c_str());
            locations.outerCutOff = GetUniformLocation((lightName +
                                                        DEF_SHADER_LIGHTS_ARRAY_LOCATION_OUTERCUTOFF_NAME).c_str());
            locations.direction = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_DIRECTION_NAME).c_str());
            locations.position = GetUniformLocation((lightName +
                                                     DEF_SHADER_LIGHTS_ARRAY_LOCATION_POSITION_NAME).c_str());
            locations.color = GetUniformLocation((lightName +
                                                  DEF_SHADER_LIGHTS_ARRAY_LOCATION_COLOR_NAME).c_str());
            locations.intensity = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_INTENSITY_NAME).c_str());
            locations.constant = GetUniformLocation((lightName +
                                                     DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_CONST_NAME).c_str());
            locations.linear = GetUniformLocation((lightName +
                                                   DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_LINEAR_NAME).c_str());
            locations.quadratic = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_QUADRATIC_NAME).c_str());

            if (locations.innerCutOff == -1 || locations.outerCutOff == -1 || locations.direction == -1 ||
                locations.position == -1 || locations.color == -1 || locations.intensity == -1 ||
                locations.constant == -1 || locations.linear == -1 || locations.quadratic == -1) {
                std::cerr
                        << "SHADER ERROR: *SPOT* LIGHTS ARRAY *ELEMENTS* NOT FOUND IN SHADER CODE, BUT WERE EXPECTED."
                        << std::endl;
                this->PrintName();

            } else {
                LightsArraySpot_UniformLocation.push_back(locations);
            }


        }
    }

    this->SaveObjectMaterialLocation();
    return *this;
}

ShaderHandler &ShaderHandler::SavePhongLightLocation() {
    this->ShineValueLocation = GetUniformLocation(DEF_SHADER_LIGHTS_BLINNPHONG_SHINEVALUE_NAME);
    this->SpecularColorLocation = GetUniformLocation(DEF_SHADER_LIGHTS_BLINNPHONG_SPECCOLOR_NAME);

    if (this->ShineValueLocation == -1 || this->SpecularColorLocation == -1) {
        std::cerr << "SHADER ERROR: BLINN-PHONG LIGHTING NOT FOUND IN SHADER CODE, BUT WAS EXPECTED."
                  << std::endl;
        this->PrintName();
    }

    return *this;
}

ShaderHandler &ShaderHandler::SaveCameraLocationLocation() {
    this->CameraLocationLocation = GetUniformLocation(DEF_SHADER_CAMERA_LOCATION_NAME);

    if (this->CameraLocationLocation == -1) {
        std::cerr << "SHADER ERROR: CAMERA LOCATION NOT FOUND IN SHADER CODE, BUT WAS EXPECTED."
                  << std::endl;
        this->PrintName();
    }

    return *this;
}


void ShaderHandler::RenderBase(const glm::mat4 &modelMatrix) {
    SendToShader(ModelMatrixLocation, modelMatrix);
    SendToShader(ViewMatrixLocation, this->ViewMatrix);
    SendToShader(ProjectionMatrixLocation, this->ProjectionMatrix);
}

void ShaderHandler::RenderNormalMatrix(const glm::mat4 &modelMatrix) const {
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
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

void ShaderHandler::RequestRenderBaseLightsArray() {
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

void ShaderHandler::RenderSkybox() const {
    glActiveTexture(GL_TEXTURE1);

// Load a cubemap texture using SOIL
    GLuint cubemapTextureID = SOIL_load_OGL_cubemap(
            "xpos.jpg", "negx.jpg",
            "ypos.jpg", "negy.jpg",
            "zpos.jpg", "negz.jpg",
            SOIL_LOAD_RGB,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS
    );

// Check for errors during loading
    if(cubemapTextureID == 0) {
        // Handle the error as appropriate
        std::cerr << "SOIL loading error: '" << SOIL_last_result() << "' (cubemap)" << std::endl;
    }

// Bind the loaded cubemap texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureID);

// Set the cubemap texture unit to the fragment shader
    GLint cubemapUniformID = glGetUniformLocation(this->ShaderProgramGLuint, DEF_SHADER_TEXTURE_CUBEMAP_LOCATION);
    glUniform1i(cubemapUniformID, 1);
}

void ShaderHandler::RequestRender(RenderableObject &object) {
    glm::mat4 modelMatrix = object.GetTransf();
    RenderBase(modelMatrix);

    if (this->CameraLocationLocation != -2) {
        this->RenderCameraLocation();
    }

    if (NormalMatrixLocation != -2) {
        RenderNormalMatrix(modelMatrix);
    }

    if (AmbientColorLocation != -2 && DiffuseColorLocation != -2) {
        this->RenderObjectMaterial(object.GetMaterial());
    }

    if (ShineValueLocation != -2 && SpecularColorLocation != -2) {
        this->RenderPhongLight(object.GetMaterial());
    }

    if (this->HaveLightsChanged) {
        this->HaveLightsChanged = false;
        this->RequestRenderBaseLightsArray();
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




