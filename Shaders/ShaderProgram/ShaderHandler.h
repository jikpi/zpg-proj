//
// Created by KOP0269 on 25.9.23.
//

#ifndef ZPG_TEST_SHADERHANDLER_H
#define ZPG_TEST_SHADERHANDLER_H

#include <cstdlib>
#include <cstdio>
#include <memory>

#include <vector>
#include <string>

#include "../Camera/CameraObserver/CameraObserver.h"
#include "../Lighting/LightPoint.h"
#include "../../Model/Material.h"
#include "../../Model/Abstract/RenderableObject.h"
#include "../Lighting/Uniforms/LightsArrayPointUniform.h"
#include "ShaderBase/ShaderBase.h"


class ShaderHandler : public ShaderBase, public CameraObserver {
private:

    bool HasCameraError{};
    bool HaveLightsChanged{};

    glm::mat4 ViewMatrix{};
    glm::mat4 ProjectionMatrix{};
    glm::vec3 CameraLocation{};

    std::weak_ptr<std::vector<std::shared_ptr<LightPoint>>> SelectedLightsFromMap;

    void RequestRenderBaseLightsArray();

    void RenderBase(const glm::mat4 &modelMatrix);
    void RenderCameraLocation() const;
    void RenderNormalMatrix(const glm::mat4 &modelMatrix) const;
    void RenderLightsArray(const std::shared_ptr<std::vector<std::shared_ptr<LightPoint>>> &lightsVector) const;
    void RenderObjectMaterial(Material objectMaterial) const;
    void RenderPhongLight(Material objectMaterial) const;


    // GLSL Shaders GLint locations
    //Base
    GLint ModelMatrixLocation{};
    GLint ViewMatrixLocation{};
    GLint ProjectionMatrixLocation{};
    GLint CameraLocationLocation{};
    //Lights
    GLint LightsArraySizeLocation{};
    std::vector<LightsArrayPointUniform> LightsArrayUniformLocation;

    //Object Material
    GLint AmbientColorLocation{};
    GLint DiffuseColorLocation{};
    //Blinn-Phong
    GLint SpecularColorLocation{};
    GLint ShineValueLocation{};


    //Normals
    GLint NormalMatrixLocation;


public:
    ShaderHandler();
    ~ShaderHandler() override;
    ShaderHandler(const ShaderHandler &) = delete;
    ShaderHandler &operator=(const ShaderHandler &) = delete;
    ShaderHandler(ShaderHandler &&other) noexcept;
    ShaderHandler &operator=(ShaderHandler &&other) noexcept;

    void PrintName() const override;

    void SetLights(std::shared_ptr<std::vector<std::shared_ptr<LightPoint>>> &lights);
    void NotifyLightsChanged();

    void RequestRender(RenderableObject &object);

    void CameraChangedNotification(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix,
                                   const glm::vec3 &cameraLocation) override;


    ShaderHandler &
    SaveBaseMatrixLocations();//Save model matrix, view matrix, projection matrix location. Assumed in every shader.
    ShaderHandler &SaveNormalsLocation();
    ShaderHandler &SaveLightingLocation();
    ShaderHandler &SavePhongLightLocation();
    ShaderHandler &SaveCameraLocationLocation();
    ShaderHandler &SaveObjectMaterialLocation();
};


#endif //ZPG_TEST_SHADERHANDLER_H
