//
// Created by KOP0269 on 10/27/23.
//

#include "ShaderHandlerFactory.h"
#include "../../ShadersCode/Loader/ShaderFileLoader.h"
#include <string>


std::shared_ptr<ShaderHandler> ShaderHandlerFactory::ConstantColored() {
    auto vertexGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadMVPNCleanVertex().c_str(),
                                                         ShaderType::VERTEX_SHADER);
    auto fragmentGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadConstantColored().c_str(),
                                                           ShaderType::FRAGMENT_SHADER);
    std::shared_ptr<ShaderHandler> shader = std::make_shared<ShaderHandler>();
    shader->AttachShaders(std::move(vertexGLSLShader), std::move(fragmentGLSLShader));
    shader->FinalizeGLSLattachment();
    shader->Name = "Constant";
    shader->SaveBaseMatrixLocations().SaveObjectMaterialLocation();

    DebugErrorMessages::PrintGLErrors("Constant shader created");

    return shader;
}

std::shared_ptr<ShaderHandler> ShaderHandlerFactory::Lambert() {
    auto vertexGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadMVPNCleanVertex().c_str(),
                                                         ShaderType::VERTEX_SHADER);
    auto fragmentGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadLambertCleanFragment().c_str(),
                                                           ShaderType::FRAGMENT_SHADER);
    std::shared_ptr<ShaderHandler> shader = std::make_shared<ShaderHandler>();
    shader->AttachShaders(std::move(vertexGLSLShader), std::move(fragmentGLSLShader));
    shader->FinalizeGLSLattachment();
    shader->Name = "Lambert";
    shader->SaveBaseMatrixLocations().SaveNormalsLocation().SaveLightingLocation();

    DebugErrorMessages::PrintGLErrors("Lambert shader created");

    return shader;
}

std::shared_ptr<ShaderHandler> ShaderHandlerFactory::Phong() {
    auto vertexGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadMVPNCleanVertex().c_str(),
                                                         ShaderType::VERTEX_SHADER);
    auto fragmentGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadPhongFragment().c_str(),
                                                           ShaderType::FRAGMENT_SHADER);
    std::shared_ptr<ShaderHandler> shader = std::make_shared<ShaderHandler>();
    shader->AttachShaders(std::move(vertexGLSLShader), std::move(fragmentGLSLShader));
    shader->FinalizeGLSLattachment();
    shader->Name = "Phong";
    shader->SaveBaseMatrixLocations().SaveNormalsLocation().SaveLightingLocation().SavePhongLightLocation().SaveCameraLocationLocation();

    DebugErrorMessages::PrintGLErrors("Phong shader created");

    return shader;
}

std::shared_ptr<ShaderHandler> ShaderHandlerFactory::BlinnPhong() {
    auto vertexGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadMVPNCleanVertex().c_str(),
                                                         ShaderType::VERTEX_SHADER);
    auto fragmentGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadBlinnPhongFragment().c_str(),
                                                           ShaderType::FRAGMENT_SHADER);
    std::shared_ptr<ShaderHandler> shader = std::make_shared<ShaderHandler>();
    shader->AttachShaders(std::move(vertexGLSLShader), std::move(fragmentGLSLShader));
    shader->FinalizeGLSLattachment();
    shader->Name = "BlinnPhong";
    shader->SaveBaseMatrixLocations().SaveNormalsLocation().SaveLightingLocation().SavePhongLightLocation().SaveCameraLocationLocation();

    DebugErrorMessages::PrintGLErrors("BlinnPhong shader created");

    return shader;
}

std::shared_ptr<ShaderHandler> ShaderHandlerFactory::Skybox() {
    auto vertexGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadCubemapSkyboxVert().c_str(),
                                                         ShaderType::VERTEX_SHADER);
    auto fragmentGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadCubemapSkyboxFrag().c_str(),
                                                           ShaderType::FRAGMENT_SHADER);
    std::shared_ptr<ShaderHandler> shader = std::make_shared<ShaderHandler>();
    shader->AttachShaders(std::move(vertexGLSLShader), std::move(fragmentGLSLShader));
    shader->FinalizeGLSLattachment();
    shader->Name = "Skybox";
    shader->SaveBaseMatrixLocations().SaveSkyboxLocation();

    DebugErrorMessages::PrintGLErrors("Skybox shader created");

    return shader;
}

std::shared_ptr<ShaderHandler> ShaderHandlerFactory::PhongTexture() {
    auto vertexGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadMVPNTextureVertex().c_str(),
                                                         ShaderType::VERTEX_SHADER);
    auto fragmentGLSLShader = std::make_unique<GLSLShader>(ShaderFileLoader::HardLoadPhongTextureFragment().c_str(),
                                                           ShaderType::FRAGMENT_SHADER);
    std::shared_ptr<ShaderHandler> shader = std::make_shared<ShaderHandler>();
    shader->AttachShaders(std::move(vertexGLSLShader), std::move(fragmentGLSLShader));
    shader->FinalizeGLSLattachment();
    shader->Name = "PhongTexture";
    shader->SaveBaseMatrixLocations().SaveNormalsLocation().SaveLightingLocation().SavePhongLightLocation().SaveCameraLocationLocation().SaveTextureLocation();

    DebugErrorMessages::PrintGLErrors("PhongTexture shader created");

    return shader;
}
