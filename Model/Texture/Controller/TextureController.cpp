//
// Created by KOP0269 on 11/9/23.
//

#include <iostream>
#include "TextureController.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <vector>

Texture *TextureController::UseTexture(const std::string &path) {
    if (Textures.find(path) == Textures.end()) {
        Textures[path] = LoadTexture(path);
        return Textures[path].get();
    }

    return Textures[path].get();
}

Texture *TextureController::UseCubemap(const std::string &path) {
    if (Textures.find(path) == Textures.end()) {
        Textures[path] = LoadCubeMap(path);
        return Textures[path].get();
    }

    return Textures[path].get();
}

std::unique_ptr<Texture> TextureController::LoadTexture(const std::string &path) {
    int width, height, nrChannels;
    std::cout << "Loading texture: " << path << std::endl;
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


std::unique_ptr<Texture> TextureController::LoadCubeMap(const std::string &path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    std::vector<std::string> filenames = {
            "negx",
            "negy",
            "negz",
            "posx",
            "posy",
            "posz"
    };

    std::vector<std::string> suffixes = {
            ".png",
            ".jpg",
            ".jpeg"
    };

    std::vector<std::string> faces;

    bool found = false;
    for (auto &filename: filenames) {
        for (auto &suffix: suffixes) {
            std::string fullPath = path;
            fullPath.append(filename);
            fullPath.append(suffix);

            if (FILE *file = fopen(fullPath.c_str(), "r")) {
                fclose(file);

                for (auto &face: filenames) {
                    std::string facePath = path;
                    facePath.append(face);
                    facePath.append(suffix);

                    faces.push_back(facePath);
                    found = true;
                }

                break;
            }

            if (found) {
                break;
            }
        }
    }

    if (!found) {
        std::cerr << "ERROR: CubeMap texture failed to load at path: " << path << std::endl;
        return nullptr;
    }

    int width, height, nrChannels;
    for (GLuint i = 0; i < faces.size(); i++) {
        std::cout << "Loading cubemap: " << faces[i] << std::endl;
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         data);
            stbi_image_free(data);
        } else {
            std::cerr << "ERROR: Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
            return nullptr;
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    std::unique_ptr<Texture> newTexture = std::make_unique<Texture>(textureID, width, height, nrChannels);
    return newTexture;
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