//
// Created by KOP0269 on 10/19/23.
//

#ifndef ZPG_TEST_SHADERFILELOADER_H
#define ZPG_TEST_SHADERFILELOADER_H


class ShaderFileLoader {
private:
    static std::string LoadShaderCodeFromFile(const char *file_path);

public:
    static std::string HardLoadMVPNCleanVertex();
    static std::string HardLoadLambertCleanFragment();
    static std::string HardLoadPhongFragment();
    static std::string HardLoadBlinnPhongFragment();
    static std::string HardLoadConstantColored();
    static std::string HardLoadConstantTrue();

    static std::string HardLoadCubemapSkyboxVert();
    static std::string HardLoadCubemapSkyboxFrag();

};


#endif //ZPG_TEST_SHADERFILELOADER_H
