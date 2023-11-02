//
// Created by KOP0269 on 11/2/23.
//

#ifndef ZPG_TEST_LIGHTSARRAYSPOTUNIFORM_H
#define ZPG_TEST_LIGHTSARRAYSPOTUNIFORM_H


#include <GL/glew.h>

class LightsArraySpotUniform {
public:
    GLint position;
    GLint direction;
    GLint color;
    GLint intensity;
    GLint constant;
    GLint linear;
    GLint quadratic;
    GLint innerCutOff;
    GLint outerCutOff;
};


#endif //ZPG_TEST_LIGHTSARRAYSPOTUNIFORM_H
