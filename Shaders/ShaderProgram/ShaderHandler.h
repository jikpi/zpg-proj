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
#include "../Lighting/Uniforms/LightArrayDirectionalUniform.h"
#include "ShaderBase/ShaderBase.h"
#include "../Lighting/Uniforms/LightsArraySpotUniform.h"


class ShaderHandler : public ShaderBase, public CameraObserver {
private:

    bool HaveLightsChanged{};

    glm::mat4 ViewMatrix{};
    glm::mat4 ProjectionMatrix{};
    glm::vec3 CameraLocation{};

    std::weak_ptr<std::vector<std::shared_ptr<RenderableLight>>> SelectedLightsFromMap;

    void RenderBaseLightsArray();

    void RenderBase(const glm::mat4 &modelMatrix);
    void RenderCameraLocation() const;
    void RenderNormalMatrix(const glm::mat4 &modelMatrix) const;
    void RenderLightsArray(const std::shared_ptr<std::vector<std::shared_ptr<RenderableLight>>> &lightsVector) const;
    void RenderObjectMaterial(Material objectMaterial) const;
    void RenderPhongLight(Material objectMaterial) const;

    static void RenderAnyTexture(Texture *texture, int target, const GLint &Location) ;
    void RenderTexture(Texture *texture) const;
    void RenderSkybox(Texture *texture) const;


    /** GLSL Shaders GLint locations **/
    /*Base*/
    GLint ModelMatrixLocation{};
    GLint ViewMatrixLocation{};
    GLint ProjectionMatrixLocation{};
    GLint CameraLocationLocation{};
    /* Normals */
    GLint NormalMatrixLocation;
    /* Lights */
    //Point Lights
    GLint LightsArrayPoint_SizeLocation{};
    std::vector<LightsArrayPointUniform> LightsArrayPoint_UniformLocation;
    //Directional Lights
    GLint LightsArrayDirectional_SizeLocation{};
    std::vector<LightArrayDirectionalUniform> LightsArrayDirectional_UniformLocation;
    //Spot Lights
    GLint LightsArraySpot_SizeLocation{};
    std::vector<LightsArraySpotUniform> LightsArraySpot_UniformLocation;
    /* Material */
    //Object Material
    GLint AmbientColorLocation{};
    GLint DiffuseColorLocation{};
    //Blinn-Phong
    GLint SpecularColorLocation{};
    GLint ShineValueLocation{};
    /* Texture */
    GLint TextureLocation{};
    /* Skybox cubemap */
    GLint SkyboxLocation{};


public:
    ShaderHandler();
    ShaderHandler(const ShaderHandler &) = delete;
    ShaderHandler &operator=(const ShaderHandler &) = delete;

    void PrintName() const override;

    void SetLights(std::shared_ptr<std::vector<std::shared_ptr<RenderableLight>>> &lights);
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
    ShaderHandler &SaveTextureLocation();
    ShaderHandler &SaveSkyboxLocation();
};


#endif //ZPG_TEST_SHADERHANDLER_H
