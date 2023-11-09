//
// Created by KOP0269 on 10/19/23.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ShaderFileLoader.h"

std::string ShaderFileLoader::LoadShaderCodeFromFile(const char *file_path) {
    std::ifstream file(file_path, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << file_path << std::endl;
        throw std::runtime_error("Failed to open shader file");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

std::string ShaderFileLoader::HardLoadMVPNCleanVertex() {
    return LoadShaderCodeFromFile("../Shaders/ShadersCode/ShaderFiles/MVPNClean.vert");
}

std::string ShaderFileLoader::HardLoadLambertCleanFragment() {
    return LoadShaderCodeFromFile("../Shaders/ShadersCode/ShaderFiles/LambertClean.frag");
}

std::string ShaderFileLoader::HardLoadBlinnPhongFragment() {
    return LoadShaderCodeFromFile("../Shaders/ShadersCode/ShaderFiles/BlinnPhongClean.frag");
}

std::string ShaderFileLoader::HardLoadPhongFragment() {
    return LoadShaderCodeFromFile("../Shaders/ShadersCode/ShaderFiles/PhongClean.frag");
}

std::string ShaderFileLoader::HardLoadConstantColored() {
    return LoadShaderCodeFromFile("../Shaders/ShadersCode/ShaderFiles/ConstantColored.frag");
}

std::string ShaderFileLoader::HardLoadConstantTrue() {
    return LoadShaderCodeFromFile("../Shaders/ShadersCode/ShaderFiles/ConstantTrue.frag");
}

std::string ShaderFileLoader::HardLoadCubemapSkyboxVert() {
    return LoadShaderCodeFromFile("../Shaders/ShadersCode/ShaderFiles/CubemapSkybox.vert");
}

std::string ShaderFileLoader::HardLoadCubemapSkyboxFrag() {
    return LoadShaderCodeFromFile("../Shaders/ShadersCode/ShaderFiles/CubemapSkybox.frag");
}
