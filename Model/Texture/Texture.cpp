//
// Created by KOP0269 on 11/9/23.
//

#include "Texture.h"

int Texture::TextureUnitCounter = 0;

Texture::Texture(GLuint textureID, int width, int height, int channels) : TextureID(textureID),
                                                                          Width(width),
                                                                          Height(height),
                                                                          Channels(channels),
                                                                          TextureUnit(-1){

}

GLuint Texture::GetTextureID() const {
    return TextureID;
}

int Texture::GetWidth() const {
    return Width;
}

int Texture::GetHeight() const {
    return Height;
}

int Texture::GetChannels() const {
    return Channels;
}

int Texture::GetTextureUnit() const {
    return TextureUnit;
}

void Texture::SetTextureUnit(int textureUnit) {
    TextureUnit = textureUnit;
}
