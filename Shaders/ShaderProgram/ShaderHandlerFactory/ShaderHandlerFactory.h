//
// Created by KOP0269 on 10/27/23.
//

#ifndef ZPG_TEST_SHADERHANDLERFACTORY_H
#define ZPG_TEST_SHADERHANDLERFACTORY_H


#include <memory>
#include "../ShaderHandler.h"

class ShaderHandlerFactory {
public:
    static std::shared_ptr<ShaderHandler> ConstantColored();
    static std::shared_ptr<ShaderHandler> Lambert();
    static std::shared_ptr<ShaderHandler> Phong();
    static std::shared_ptr<ShaderHandler> BlinnPhong();

    static std::shared_ptr<ShaderHandler> PhongTexture();

    static std::shared_ptr<ShaderHandler> Skybox();

    static std::shared_ptr<ShaderHandler> Crosshair();
};


#endif //ZPG_TEST_SHADERHANDLERFACTORY_H
