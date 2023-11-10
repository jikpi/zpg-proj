//
// Created by KOP0269 on 11/9/23.
//

#ifndef ZPG_TEST_TEXTURECONTROLLER_H
#define ZPG_TEST_TEXTURECONTROLLER_H


#include <string>
#include <map>
#include <memory>
#include "../Texture.h"

class TextureController {
private:
    static std::unique_ptr<Texture> LoadTexture(const std::string &path);
    static std::unique_ptr<Texture> LoadCubeMap(const std::string &path);

    std::map<std::string, std::unique_ptr<Texture>> Textures;

public:
    Texture *UseTexture(const std::string &path);
    Texture *UseCubemap(const std::string &path);
    void ResetTextureUnitCounter();
};


#endif //ZPG_TEST_TEXTURECONTROLLER_H
