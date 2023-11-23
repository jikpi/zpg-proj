//
// Created by KOP0269 on 11/9/23.
//

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <vector>

#include "TextureController.h"
#include "../../../Application/Configuration/AGlobalConfig.h"

Texture *TextureController::UseTexture(const std::string &path, bool standardPath) {

    std::string fullPath = path;
    if (standardPath) {
        fullPath = DEF_PATH_TEXTURES + path;
    }

    if (Textures.find(fullPath) == Textures.end()) {
        Textures[fullPath] = LoadTexture(fullPath);
        return Textures[fullPath].get();
    }

    return Textures[fullPath].get();
}

Texture *TextureController::UseCubemap(const std::string &path, bool standardPath) {

    std::string fullPath = path;
    if (standardPath) {
        fullPath = DEF_PATH_TEXTURES + path;
    }

    if (Textures.find(fullPath) == Textures.end()) {
        Textures[fullPath] = LoadCubeMap(fullPath);
        return Textures[fullPath].get();
    }

    return Textures[fullPath].get();
}

std::unique_ptr<Texture> TextureController::LoadTexture(const std::string &path) {
    int width, height, nrChannels;
    std::cout << "Loading texture: " << path << std::endl;

    stbi_set_flip_vertically_on_load(true);
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
    glBindTexture(GL_TEXTURE_2D, 0);
    return newTexture;
}


std::unique_ptr<Texture> TextureController::LoadCubeMap(const std::string &path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    std::vector<std::string> faces = {
            "posx", "negx", "posy", "negy", "posz", "negz"
    };
    std::vector<std::string> suffixes = {".png", ".jpg", ".jpeg"};

    std::vector<std::string> facePaths(6);
    bool allFacesFound = true;

    for (size_t i = 0; i < faces.size() && allFacesFound; ++i) {
        bool faceFound = false;
        for (const auto &suffix: suffixes) {
            std::string fullPath = path + faces[i] + suffix;
            if (FILE *file = fopen(fullPath.c_str(), "r")) {
                fclose(file);
                facePaths[i] = fullPath;
                faceFound = true;
                break;
            }
        }
        if (!faceFound) {
            //Am image is missing
            allFacesFound = false;
        }
    }

    bool usingSingleTexture = false;
    if (!allFacesFound) {
        for (const auto &suffix: suffixes) {
            std::string fullPath = path + suffix;
            if (FILE *file = fopen(fullPath.c_str(), "r")) {
                fclose(file);
                facePaths.assign(6, fullPath);
                usingSingleTexture = true;
                break;
            }
        }

        //No image found
        if (!usingSingleTexture) {
            std::cerr << "ERROR: CubeMap texture failed to load at path: " << path << std::endl;
            glDeleteTextures(1, &textureID);
            return nullptr;
        }
    }

    //Load the images
    int width, height, nrChannels;
    unsigned char *data = nullptr;
    for (GLuint i = 0; i < facePaths.size(); ++i) {
        if (!usingSingleTexture || (usingSingleTexture && i == 0)) {
            std::cout << "Loading cubemap face: " << facePaths[i] << std::endl;
            data = stbi_load(facePaths[i].c_str(), &width, &height, &nrChannels, 0);
            if (!data) {
                std::cerr << "ERROR: Cubemap texture failed to load at path: " << facePaths[i] << std::endl;
                stbi_image_free(data);
                glDeleteTextures(1, &textureID);
                return nullptr;
            }
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        if (!usingSingleTexture) {
            stbi_image_free(data);
        }
    }

    if (usingSingleTexture && data) {
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    return std::make_unique<Texture>(textureID, width, height, nrChannels);
}


void TextureController::ResetTextureUnitCounter() {
    Texture::TextureUnitCounter = 0;

    for (auto &texture: Textures) {
        if (!texture.second) {
            std::cerr << "ERROR: Texture not found: " << texture.first << std::endl;
            continue;
        }

        texture.second->SetTextureUnit(-1);
    }
}