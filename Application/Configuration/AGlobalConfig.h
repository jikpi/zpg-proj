//
// Created by KOP0269 on 10/17/23.
//

#ifndef ZPG_TEST_AGLOBALCONFIG_H
#define ZPG_TEST_AGLOBALCONFIG_H

#include "glm/vec3.hpp"

//// ### Camera ###
inline constexpr float DEF_CAMERA_FOV = 60.0f;
inline constexpr float DEF_CAMERA_ASPECTRATIO = 4.0f / 3.0f;
inline constexpr float DEF_CAMERA_MINRENDER = 0.1f;
inline constexpr float DEF_CAMERA_MAXRENDER = 1000.0f;

//// ### Map ###
inline constexpr const char *DEF_MAP_NAME = "Default";
inline constexpr const int DEF_MAP_CHANGE_TIMEOUT = 10;

//// ### ShaderProgram ###
// model matrix, view matrix, projection matrix
inline constexpr const char *DEF_SHADER_MODEL_MATRIX_NAME = "modelMatrix";
inline constexpr const char *DEF_SHADER_VIEW_MATRIX_NAME = "viewMatrix";
inline constexpr const char *DEF_SHADER_PROJECTION_MATRIX_NAME = "projectionMatrix";
//Normal matrix
inline constexpr const char *DEF_SHADER_NORMAL_MATRIX_NAME = "normalMatrix";
//Camera shader location
inline constexpr const char *DEF_SHADER_CAMERA_LOCATION_NAME = "cameraLocation";
//Lights array
inline constexpr const int DEF_SHADER_LIGHTS_ARRAY_LOCATION_ARRAY_SIZE = 16;
//#Point
inline constexpr const char *DEF_SHADER_LIGHTS_POINT_ARRAY_LOCATION_SIZE_NAME = "LightPointSize";
inline constexpr const char *DEF_SHADER_LIGHTS_POINT_ARRAY_LOCATION_NAME = "LightPointArray";
//#Directional
inline constexpr const char *DEF_SHADER_LIGHTS_DIRECTIONAL_ARRAY_LOCATION_SIZE_NAME = "LightDirectionalSize";
inline constexpr const char *DEF_SHADER_LIGHTS_DIRECTIONAL_ARRAY_LOCATION_NAME = "LightDirectionalArray";
//#Spot
inline constexpr const char *DEF_SHADER_LIGHTS_SPOT_ARRAY_LOCATION_SIZE_NAME = "LightSpotSize";
inline constexpr const char *DEF_SHADER_LIGHTS_SPOT_ARRAY_LOCATION_NAME = "LightSpotArray";
//Struct fields
inline constexpr const char *DEF_SHADER_LIGHTS_ARRAY_LOCATION_INNERCUTOFF_NAME = "innerCutOff";
inline constexpr const char *DEF_SHADER_LIGHTS_ARRAY_LOCATION_OUTERCUTOFF_NAME = "outerCutOff";
inline constexpr const char *DEF_SHADER_LIGHTS_ARRAY_LOCATION_DIRECTION_NAME = "direction";
inline constexpr const char *DEF_SHADER_LIGHTS_ARRAY_LOCATION_POSITION_NAME = "position";
inline constexpr const char *DEF_SHADER_LIGHTS_ARRAY_LOCATION_COLOR_NAME = "color";
inline constexpr const char *DEF_SHADER_LIGHTS_ARRAY_LOCATION_INTENSITY_NAME = "intensity";
inline constexpr const char *DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_CONST_NAME = "constant";
inline constexpr const char *DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_LINEAR_NAME = "linear";
inline constexpr const char *DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_QUADRATIC_NAME = "quadratic";
//Material
inline constexpr const char *DEF_SHADER_MATERIAL_AMBIENTCOLOR_NAME = "ambientColor";
inline constexpr const char *DEF_SHADER_MATERIAL_DIFFUSECOLOR_NAME = "diffuseColor";
//Blinn-Phong
inline constexpr const char *DEF_SHADER_LIGHTS_BLINNPHONG_SPECCOLOR_NAME = "specularColor";
inline constexpr const char *DEF_SHADER_LIGHTS_BLINNPHONG_SHINEVALUE_NAME = "shineValue";
//Texture
inline constexpr const char *DEF_SHADER_TEXTURE_TWOD_LOCATION= "twoDTexture";
inline constexpr const char *DEF_SHADER_TEXTURE_CUBEMAP_LOCATION= "cubemapTexture";

//// ### Lights ###
inline constexpr const float DEF_LIGHT_INTENSITY = 1.0f;
inline constexpr const float DEF_LIGHT_CONSTANT = 1.0f;
inline constexpr const float DEF_LIGHT_LINEAR = 0.09f;
inline constexpr const float DEF_LIGHT_QUADRATIC = 0.1f;
inline constexpr const glm::vec3 DEF_LIGHT_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
inline constexpr const glm::vec3 DEF_LIGHT_DIRECTIONAL_DIRECTION = glm::vec3(0.0f, -1.0f, 0.0f);
inline constexpr const float DEF_LIGHT_INNERCUTOFF = 10.0f;
inline constexpr const float DEF_LIGHT_OUTERCUTOFF = 20.0f;

//// ### Standard paths ###
inline constexpr const char *DEF_PATH_TEXTURES = "../Resources/Textures/";
inline constexpr const char *DEF_PATH_MODELS = "../Resources/Models/";

//// ### Stencil / Context ###
inline constexpr const unsigned short DEF_CONTEXT_DEFAULT_ID = 1;
inline constexpr const unsigned short DEF_CONTEXT_ERROR_ID = 0;
inline constexpr const unsigned int DEF_CONTEXT_MAX = 255;

//// ### Animations ###
inline constexpr const float DEF_ANIMATION_BEZIER_SMOOTH_T_DIFF = 0.05f;

#endif //ZPG_TEST_AGLOBALCONFIG_H
