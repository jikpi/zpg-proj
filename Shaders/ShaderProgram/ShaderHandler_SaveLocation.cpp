//
// Created by lvi on 23.11.23.
//


#include <iostream>
#include "ShaderHandler.h"
#include "../../Application/Configuration/AGlobalConfig.h"

ShaderHandler &ShaderHandler::SaveBaseMatrixLocations() {
    ModelMatrixLocation = GetUniformLocation(DEF_SHADER_MODEL_MATRIX_NAME);
    ViewMatrixLocation = GetUniformLocation(DEF_SHADER_VIEW_MATRIX_NAME);
    ProjectionMatrixLocation = GetUniformLocation(DEF_SHADER_PROJECTION_MATRIX_NAME);

    if ((ModelMatrixLocation == -1 || ViewMatrixLocation == -1 || ProjectionMatrixLocation == -1)) {
        std::cerr << "SHADER ERROR: A BASIC TRANSFORMATION NOT FOUND IN SHADER CODE." << std::endl;
        if (ModelMatrixLocation == -1) std::cerr << "ModelMatrix == -1" << std::endl;
        if (ViewMatrixLocation == -1) std::cerr << "ViewMatrix == -1" << std::endl;
        if (ProjectionMatrixLocation == -1) std::cerr << "ProjectionMatrix == -1" << std::endl;
        this->PrintName();
    }

    return *this;
}

ShaderHandler &ShaderHandler::SaveNormalsLocation() {
    NormalMatrixLocation = GetUniformLocation(DEF_SHADER_NORMAL_MATRIX_NAME);
    if (NormalMatrixLocation == -1) {
        std::cerr << "SHADER ERROR: NORMAL MATRIX NOT FOUND IN SHADER CODE, BUT WAS EXPECTED." << std::endl;
        this->PrintName();
    }

    return *this;
}

ShaderHandler &ShaderHandler::SaveObjectMaterialLocation() {
    AmbientColorLocation = GetUniformLocation(DEF_SHADER_MATERIAL_AMBIENTCOLOR_NAME);
    DiffuseColorLocation = GetUniformLocation(DEF_SHADER_MATERIAL_DIFFUSECOLOR_NAME);

    if (AmbientColorLocation == -1 || DiffuseColorLocation == -1) {
        std::cerr << "SHADER ERROR: MATERIAL NOT FOUND IN SHADER CODE, BUT WAS EXPECTED." << std::endl;
        if (AmbientColorLocation == -1) std::cerr << "AmbientColorLocation == -1" << std::endl;
        if (DiffuseColorLocation == -1) std::cerr << "DiffuseColorLocation == -1" << std::endl;
        this->PrintName();
    }

    return *this;
}

ShaderHandler &ShaderHandler::SaveLightingLocation() {

    //Point Lights
    this->LightsArrayPoint_SizeLocation = GetUniformLocation(DEF_SHADER_LIGHTS_POINT_ARRAY_LOCATION_SIZE_NAME);
    if (LightsArrayPoint_SizeLocation == -1) {
        std::cerr << "SHADER ERROR: *POINT* LIGHTS ARRAY NOT FOUND IN SHADER CODE, BUT WAS EXPECTED." << std::endl;
        this->PrintName();
    } else {
        std::string lightsArrayBaseName = DEF_SHADER_LIGHTS_POINT_ARRAY_LOCATION_NAME;
        for (int i = 0; i < DEF_SHADER_LIGHTS_ARRAY_LOCATION_ARRAY_SIZE; i++) {
            std::string lightName = lightsArrayBaseName + "[" + std::to_string(i) + "].";
            LightsArrayPointUniform locations{};
            locations.position = GetUniformLocation((lightName +
                                                     DEF_SHADER_LIGHTS_ARRAY_LOCATION_POSITION_NAME).c_str());
            locations.color = GetUniformLocation((lightName +
                                                  DEF_SHADER_LIGHTS_ARRAY_LOCATION_COLOR_NAME).c_str());
            locations.intensity = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_INTENSITY_NAME).c_str());
            locations.constant = GetUniformLocation((lightName +
                                                     DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_CONST_NAME).c_str());
            locations.linear = GetUniformLocation((lightName +
                                                   DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_LINEAR_NAME).c_str());
            locations.quadratic = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_QUADRATIC_NAME).c_str());

            if (locations.position == -1 || locations.color == -1 || locations.intensity == -1 ||
                locations.constant == -1 || locations.linear == -1 || locations.quadratic == -1) {
                std::cerr
                        << "SHADER ERROR: *POINT* LIGHTS ARRAY *ELEMENTS* NOT FOUND IN SHADER CODE, BUT WERE EXPECTED."
                        << std::endl;
                this->PrintName();
            } else {
                LightsArrayPoint_UniformLocation.push_back(locations);
            }
        }
    }

    //Directional Lights
    this->LightsArrayDirectional_SizeLocation = GetUniformLocation(
            DEF_SHADER_LIGHTS_DIRECTIONAL_ARRAY_LOCATION_SIZE_NAME);
    if (LightsArrayDirectional_SizeLocation == -1) {
        std::cerr << "SHADER ERROR: *DIRECTIONAL* LIGHTS ARRAY NOT FOUND IN SHADER CODE, BUT WAS EXPECTED."
                  << std::endl;
        this->PrintName();
    } else {
        std::string lightsArrayBaseName = DEF_SHADER_LIGHTS_DIRECTIONAL_ARRAY_LOCATION_NAME;
        for (int i = 0; i < DEF_SHADER_LIGHTS_ARRAY_LOCATION_ARRAY_SIZE; i++) {
            std::string lightName = lightsArrayBaseName + "[" + std::to_string(i) + "].";
            LightArrayDirectionalUniform locations{};
            locations.direction = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_DIRECTION_NAME).c_str());
            locations.color = GetUniformLocation((lightName +
                                                  DEF_SHADER_LIGHTS_ARRAY_LOCATION_COLOR_NAME).c_str());
            locations.intensity = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_INTENSITY_NAME).c_str());

            if (locations.direction == -1 || locations.color == -1 || locations.intensity == -1) {
                std::cerr
                        << "SHADER ERROR: *DIRECTIONAL* LIGHTS ARRAY *ELEMENTS* NOT FOUND IN SHADER CODE, BUT WERE EXPECTED."
                        << std::endl;
                this->PrintName();
            } else {
                LightsArrayDirectional_UniformLocation.push_back(locations);
            }
        }
    }

    //Spot lights
    this->LightsArraySpot_SizeLocation = GetUniformLocation(DEF_SHADER_LIGHTS_SPOT_ARRAY_LOCATION_SIZE_NAME);
    if (LightsArraySpot_SizeLocation == -1) {
        std::cerr << "SHADER ERROR: *SPOT* LIGHTS ARRAY NOT FOUND IN SHADER CODE, BUT WAS EXPECTED." << std::endl;
        this->PrintName();
    } else {
        std::string lightsArrayBaseName = DEF_SHADER_LIGHTS_SPOT_ARRAY_LOCATION_NAME;
        for (int i = 0; i < DEF_SHADER_LIGHTS_ARRAY_LOCATION_ARRAY_SIZE; i++) {
            std::string lightName = lightsArrayBaseName + "[" + std::to_string(i) + "].";
            LightsArraySpotUniform locations{};
            locations.innerCutOff = GetUniformLocation((lightName +
                                                        DEF_SHADER_LIGHTS_ARRAY_LOCATION_INNERCUTOFF_NAME).c_str());
            locations.outerCutOff = GetUniformLocation((lightName +
                                                        DEF_SHADER_LIGHTS_ARRAY_LOCATION_OUTERCUTOFF_NAME).c_str());
            locations.direction = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_DIRECTION_NAME).c_str());
            locations.position = GetUniformLocation((lightName +
                                                     DEF_SHADER_LIGHTS_ARRAY_LOCATION_POSITION_NAME).c_str());
            locations.color = GetUniformLocation((lightName +
                                                  DEF_SHADER_LIGHTS_ARRAY_LOCATION_COLOR_NAME).c_str());
            locations.intensity = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_INTENSITY_NAME).c_str());
            locations.constant = GetUniformLocation((lightName +
                                                     DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_CONST_NAME).c_str());
            locations.linear = GetUniformLocation((lightName +
                                                   DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_LINEAR_NAME).c_str());
            locations.quadratic = GetUniformLocation((lightName +
                                                      DEF_SHADER_LIGHTS_ARRAY_LOCATION_ATTN_QUADRATIC_NAME).c_str());

            if (locations.innerCutOff == -1 || locations.outerCutOff == -1 || locations.direction == -1 ||
                locations.position == -1 || locations.color == -1 || locations.intensity == -1 ||
                locations.constant == -1 || locations.linear == -1 || locations.quadratic == -1) {
                std::cerr
                        << "SHADER ERROR: *SPOT* LIGHTS ARRAY *ELEMENTS* NOT FOUND IN SHADER CODE, BUT WERE EXPECTED."
                        << std::endl;
                this->PrintName();

            } else {
                LightsArraySpot_UniformLocation.push_back(locations);
            }


        }
    }

    this->SaveObjectMaterialLocation();
    return *this;
}

ShaderHandler &ShaderHandler::SavePhongLightLocation() {
    this->ShineValueLocation = GetUniformLocation(DEF_SHADER_LIGHTS_BLINNPHONG_SHINEVALUE_NAME);
    this->SpecularColorLocation = GetUniformLocation(DEF_SHADER_LIGHTS_BLINNPHONG_SPECCOLOR_NAME);

    if (this->ShineValueLocation == -1 || this->SpecularColorLocation == -1) {
        std::cerr << "SHADER ERROR: BLINN-PHONG LIGHTING NOT FOUND IN SHADER CODE, BUT WAS EXPECTED."
                  << std::endl;
        this->PrintName();
    }

    return *this;
}

ShaderHandler &ShaderHandler::SaveCameraLocationLocation() {
    this->CameraLocationLocation = GetUniformLocation(DEF_SHADER_CAMERA_LOCATION_NAME);

    if (this->CameraLocationLocation == -1) {
        std::cerr << "SHADER ERROR: CAMERA LOCATION NOT FOUND IN SHADER CODE, BUT WAS EXPECTED."
                  << std::endl;
        this->PrintName();
    }

    return *this;
}

ShaderHandler &ShaderHandler::SaveTextureLocation() {
    this->TextureLocation = GetUniformLocation(DEF_SHADER_TEXTURE_TWOD_LOCATION);
    if (this->TextureLocation == -1) {
        std::cerr << "SHADER ERROR: TEXTURE NOT FOUND IN SHADER CODE, BUT WAS EXPECTED."
                  << std::endl;
        this->PrintName();
    }
    return *this;
}

ShaderHandler &ShaderHandler::SaveSkyboxLocation() {
    this->SkyboxLocation = GetUniformLocation(DEF_SHADER_TEXTURE_CUBEMAP_LOCATION);
    if (this->SkyboxLocation == -1) {
        std::cerr << "SHADER ERROR: SKYBOX CUBEMAP NOT FOUND IN SHADER CODE, BUT WAS EXPECTED."
                  << std::endl;
        this->PrintName();
    }
    return *this;
}