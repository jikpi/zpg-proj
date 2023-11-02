//
// Created by KOP0269 on 10/17/23.
//

#ifndef ZPG_TEST_AGLOBALCONFIG_H
#define ZPG_TEST_AGLOBALCONFIG_H

#include "glm/vec3.hpp"

// ### Camera ###
inline constexpr float DEF_CAMERA_FOV = 60.0f;
inline constexpr float DEF_CAMERA_ASPECTRATIO = 4.0f / 3.0f;
inline constexpr float DEF_CAMERA_MINRENDER = 0.1f;
inline constexpr float DEF_CAMERA_MAXRENDER = 1000.0f;

// ### ShaderProgram ###
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
inline constexpr const char *DEF_SHADER_LIGHTS_POINT_ARRAY_LOCATION_SIZE_NAME = "LightPointSize";
inline constexpr const char *DEF_SHADER_LIGHTS_POINT_ARRAY_LOCATION_NAME = "LightPointArray";
inline constexpr const char *DEF_SHADER_LIGHTS_DIRECTIONAL_ARRAY_LOCATION_SIZE_NAME = "LightDirectionalSize";
inline constexpr const char *DEF_SHADER_LIGHTS_DIRECTIONAL_ARRAY_LOCATION_NAME = "LightDirectionalArray";
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

// ### Lights ###
inline constexpr const float DEF_LIGHT_INTENSITY = 1.0f;
inline constexpr const float DEF_LIGHT_CONSTANT = 1.0f;
inline constexpr const float DEF_LIGHT_LINEAR = 0.09f;
inline constexpr const float DEF_LIGHT_QUADRATIC = 0.1f;
inline constexpr const glm::vec3 DEF_LIGHT_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
inline constexpr const glm::vec3 DEF_LIGHT_DIRECTIONAL_DIRECTION = glm::vec3(0.0f, -1.0f, 0.0f);

#endif //ZPG_TEST_AGLOBALCONFIG_H
