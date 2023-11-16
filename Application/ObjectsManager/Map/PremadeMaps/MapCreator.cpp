//
// Created by lvi on 11/16/23.
//

#include "MapCreator.h"

ShaderHandler *MapCreator::SelectShader(std::vector<std::shared_ptr<ShaderHandler>> &shaders, const std::string &name) {
    for (auto &shader : shaders) {
        if (shader->Name == name) {
            return shader.get();
        }
    }
    return nullptr;
}

std::shared_ptr<Map>
MapCreator::FourSpheres(std::string mapName, std::vector<std::shared_ptr<ShaderHandler>> &shaders,
                        TextureController &textureController, ModelController &modelController) {

}
