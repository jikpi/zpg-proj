//
// Created by KOP0269 on 10/8/23.
//

#include "LegacyShadersStrings.h"

const char *ShaderString_VertexOG =
        "#version 330\n"
        "layout(location=0) in vec3 vp;\n"
        "void main () {\n"
        "     gl_Position = vec4 (vp, 1.0);\n"
        "}";


const char *ShaderString_FragmentOG =
        "#version 330\n"
        "out vec4 frag_colour;\n"
        "void main () {\n"
        "     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);\n"
        "}";

const char *ShaderString_VertexXYZRGB =
        "#version 330\n"
        "layout(location=0) in vec3 vp; //vertex position\n"
        "layout(location=1) in vec3 color; //vertex color\n"
        "\n"
        "out vec3 vColor; //color for fragment shader\n"
        "\n"
        "void main () {\n"
        "    gl_Position = vec4 (vp, 1.0);\n"
        "    vColor = color;\n"
        "}";


const char *ShaderString_VertexXYZRGBT =
        "#version 330\n"
        "layout(location=0) in vec3 vp; //vertex position\n"
        "layout(location=1) in vec3 color; //vertex color\n"
        "\n"
        "out vec3 vColor; //color for fragment shader\n"
        "\n"
        "uniform mat4 modelMatrix; //tranformation matrix\n"
        "\n"
        "void main () {\n"
        "    gl_Position = modelMatrix * vec4 (vp, 1.0); //do transformation\n"
        "    vColor = color;\n"
        "}";

const char *ShaderString_FragmentXYZRGB =
        "#version 330\n"
        "in vec3 vColor; //get color from vertex\n"
        "out vec4 frag_colour;\n"
        "\n"
        "void main () {\n"
        "    frag_colour = vec4 (vColor, 1.0); //use color\n"
        "}";

const char*ShaderString_FragmentXYZK =
        "#version 330\n"
        "in vec3 vColor; //get color from vertex\n"
        "out vec4 frag_colour;\n"
        "\n"
        "void main () {\n"
        "    vec3 color = vec3(0.0, 1.0, 0.0);\n"
        "    frag_colour = vec4 (color, 1.0);\n"
        "}";

const char *ShaderString_VertexXYZRGBTC =
        "#version 330\n"
        "layout(location=0) in vec3 vp; //vertex position\n"
        "layout(location=1) in vec3 color; //vertex color\n"
        "\n"
        "out vec3 vColor; //color for fragment shader\n"
        "\n"
        "uniform mat4 modelMatrix; //tranformation matrix\n"
        "uniform mat4 viewMatrix; //camera view matrix\n"
        "uniform mat4 projectionMatrix; //camera projection matrix\n"
        "\n"
        "void main () {\n"
        "    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0); //do transformation\n"
        "    vColor = color;\n"
        "}";