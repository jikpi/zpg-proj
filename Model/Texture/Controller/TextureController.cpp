//
// Created by KOP0269 on 11/9/23.
//

#include <iostream>
#include "TextureController.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

std::unique_ptr<Texture> TextureController::LoadTexture(const std::string &path) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (!data) {
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        return nullptr;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    GLenum format = GL_RGB;
    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    std::unique_ptr<Texture> newTexture = std::make_unique<Texture>(textureID, width, height, nrChannels);
    return newTexture;
}

Texture *TextureController::UseTexture(const std::string &path) {
    if (Textures.find(path) == Textures.end()) {
        Textures[path] = LoadTexture(path);
        return Textures[path].get();
    }

    return Textures[path].get();
}

void TextureController::ResetTextureUnitCounter() {
    Texture::TextureUnitCounter = 0;

    for (auto &texture: Textures) {
        //check if texture exists
        if (!texture.second) {
            std::cerr << "ERROR: Texture not found: " << texture.first << std::endl;
            continue;
        }

        texture.second->SetTextureUnit(-1);
    }
}


