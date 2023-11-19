//
// Created by lvi on 11/16/23.
//

#include <iostream>
#include "MapCreator.h"

ShaderHandler *MapCreator::SelectShader(std::vector<std::shared_ptr<ShaderHandler>> &shaders, const std::string &name) {
    for (auto &shader: shaders) {
        if (shader->Name == name) {
            return shader.get();
        }
    }
    std::cerr << "ERROR: Engine: Shader name \"" << name << "\" not found. Returning any shader." << std::endl;

    if (shaders.empty()) {
        std::cerr << "FATAL: Engine: No shaders available." << std::endl;
        throw std::runtime_error("No shaders available.");
    }

    return shaders.at(0).get();
}
