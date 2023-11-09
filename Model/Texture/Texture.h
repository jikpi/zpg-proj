//
// Created by KOP0269 on 11/9/23.
//

#ifndef ZPG_TEST_TEXTURE_H
#define ZPG_TEST_TEXTURE_H


#include <GL/glew.h>

class Texture {
private:
    GLuint TextureID;
    int Width;
    int Height;
    int Channels;

    int TextureUnit;
public:
    Texture(GLuint textureID, int width, int height, int channels);

    [[nodiscard]] GLuint GetTextureID() const;
    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    [[nodiscard]] int GetChannels() const;

    [[nodiscard]] int GetTextureUnit() const;
    void SetTextureUnit(int textureUnit);

    static int TextureUnitCounter;
};


#endif //ZPG_TEST_TEXTURE_H
