//
// Created by KOP0269 on 10/27/23.
//

#ifndef ZPG_TEST_LIGHTSARRAYPOINTUNIFORM_H
#define ZPG_TEST_LIGHTSARRAYPOINTUNIFORM_H


#include <GL/glew.h>

class LightsArrayPointUniform {
public:
    GLint position;
    GLint color;
    GLint intensity;
    GLint constant;
    GLint linear;
    GLint quadratic;
};


#endif //ZPG_TEST_LIGHTSARRAYPOINTUNIFORM_H
