//
// Created by lvi on 11/16/23.
//

#ifndef ZPG_TEST_MAPCREATOR_H
#define ZPG_TEST_MAPCREATOR_H


#include <memory>
#include "../Map.h"
#include "../../../../Model/Texture/Controller/TextureController.h"
#include "../../../../Model/Controller/ModelController.h"
#include "../ResourcesManager.h"

class MapCreator {
private:
    static ShaderHandler *SelectShader(std::vector<std::shared_ptr<ShaderHandler>> &shaders, const std::string &name);
public:


    static void
    FourSpheres(const std::string &mapName, std::vector<std::shared_ptr<ShaderHandler>> &shaders, ResourcesManager *mapManager);
    static void
    SolarSystem(std::vector<std::shared_ptr<ShaderHandler>> &shaders, ResourcesManager *mapManager);
    static void
    Overworld(const std::string &mapName, std::vector<std::shared_ptr<ShaderHandler>> &shaders, ResourcesManager *mapManager);

};


#endif //ZPG_TEST_MAPCREATOR_H
