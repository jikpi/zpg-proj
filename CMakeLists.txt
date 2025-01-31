cmake_minimum_required(VERSION 3.26)

project(zpg_test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

add_executable(zpg_test main.cpp
        Model/Abstract/BaseModelData.cpp
        Model/Abstract/BaseModelData.h
        Application/Engine.cpp
        Application/Engine.h
        Shaders/GLSLShader.cpp
        Shaders/GLSLShader.h
        Shaders/ShaderProgram/ShaderHandler.cpp
        Shaders/ShaderProgram/ShaderHandler.h
        Model/Factory/ModelFactory.cpp
        Model/Factory/ModelFactory.h
        Model/StandardisedModel.cpp
        Model/StandardisedModel.h
        Application/Managers/EngineResources/Map.cpp
        Application/Managers/EngineResources/Map.h
        Application/InputHandler/KeyCallbacks/KeyCallbacks.cpp
        Application/InputHandler/KeyCallbacks/KeyCallbacks.h
        Application/DebugErrorMessages/DebugErrorMessages.cpp
        Application/DebugErrorMessages/DebugErrorMessages.h
        Shaders/ShadersCode/LegacyShaderStrings/LegacyShadersStrings.h
        Shaders/ShadersCode/LegacyShaderStrings/LegacyShaderStrings.cpp
        Transformations/Composite/Abstract/Transformation.h
        Transformations/Composite/Transformations/Rotate.cpp
        Transformations/Composite/Transformations/Rotate.h
        Transformations/Composite/Transformations/Move.cpp
        Transformations/Composite/Transformations/Move.h
        Transformations/Composite/Transformations/Scale.cpp
        Transformations/Composite/Transformations/Scale.h
        Transformations/Composite/TransfComposite.cpp
        Transformations/Composite/TransfComposite.h
        Transformations/Composite/Factory/TransformationFactory.cpp
        Transformations/Composite/Factory/TransformationFactory.h
        Shaders/Camera/Camera.cpp
        Shaders/Camera/Camera.h
        Application/InputHandler/MovesetInputManager.cpp
        Application/InputHandler/MovesetInputManager.h
        Shaders/Camera/CameraObserver/CameraObserver.h
        Application/Configuration/AGlobalConfig.h
        Shaders/ShadersCode/Loader/ShaderFileLoader.cpp
        Shaders/ShadersCode/Loader/ShaderFileLoader.h
        Shaders/Lighting/LightPoint.cpp
        Shaders/Lighting/LightPoint.h
        Application/Managers/ShaderLinking/MapToShaderLinker.cpp
        Application/Managers/ShaderLinking/MapToShaderLinker.h
        Application/Managers/ShaderLinking/ShaderObjectSet/ShaderObjectSet.cpp
        Application/Managers/ShaderLinking/ShaderObjectSet/ShaderObjectSet.h
        Shaders/ShaderType.h
        Model/Material.cpp
        Model/Material.h
        Model/Abstract/RenderableObject.cpp
        Model/Abstract/RenderableObject.h
        Shaders/ShaderProgram/ShaderHandlerFactory/ShaderHandlerFactory.cpp
        Shaders/ShaderProgram/ShaderHandlerFactory/ShaderHandlerFactory.h
        Shaders/Lighting/Uniforms/LightsArrayPointUniform.h
        Shaders/ShaderProgram/ShaderBase/ShaderBase.cpp
        Shaders/ShaderProgram/ShaderBase/ShaderBase.h
        Application/Managers/EngineResources/ResourcesManager.cpp
        Application/Managers/EngineResources/ResourcesManager.h
        Shaders/Lighting/Abstract/RenderableLight.cpp
        Shaders/Lighting/Abstract/RenderableLight.h
        Shaders/Lighting/Abstract/LightType.h
        Shaders/Lighting/LightDirectional.cpp
        Shaders/Lighting/LightDirectional.h
        Shaders/Lighting/LightSpot.cpp
        Shaders/Lighting/LightSpot.h
        Shaders/Lighting/Uniforms/LightArrayDirectionalUniform.h
        Shaders/Lighting/Uniforms/LightsArraySpotUniform.h
        Model/Texture/Controller/TextureController.cpp
        Model/Texture/Controller/TextureController.h
        Model/Texture/Texture.cpp
        Model/Texture/Texture.h
        Model/Controller/ModelController.cpp
        Model/Controller/ModelController.h
        Model/ModelStamp.h
        Application/Managers/EngineResources/PremadeMaps/MapCreator.cpp
        Application/Managers/EngineResources/PremadeMaps/MapCreator.h
        Application/Managers/EngineResources/PremadeMaps/MapCreator_4Spheres.cpp
        Application/Managers/EngineResources/PremadeMaps/MapCreator_SolarSystem.cpp
        Application/Managers/EngineResources/PremadeMaps/MapCreator_Overworld.cpp
        Shaders/ShaderProgram/ShaderHandler_SaveLocation.cpp
        Shaders/ShaderProgram/ShaderHandler_Render.cpp
        Model/Animation/Abstract/AnyAnimation.cpp
        Model/Animation/Abstract/AnyAnimation.h
        Model/Animation/BezierAnimation.cpp
        Model/Animation/BezierAnimation.h
        Application/GameLogic/Abstract/AnyGameLogic.cpp
        Application/GameLogic/Abstract/AnyGameLogic.h
        "Application/GameLogic/Solar system/GameLogic_SolarSystem.cpp"
        "Application/GameLogic/Solar system/GameLogic_SolarSystem.h"
        Application/GameLogic/Overworld/GameLogic_Overworld.cpp
        Application/GameLogic/Overworld/GameLogic_Overworld.h
        "Application/GameLogic/Solar system/GameLogic_SolarSystem_LoadMap.cpp"
        Application/GameLogic/Overworld/GameLogic_Overworld_LoadMap.cpp
        "Application/GameLogic/4 Spheres/GameLogic_4Spheres.cpp"
        "Application/GameLogic/4 Spheres/GameLogic_4Spheres.h"
        "Application/GameLogic/4 Spheres/GameLogic_4Spheres_LoadMap.cpp"
)

target_include_directories(zpg_test PRIVATE ${ASSIMP_INCLUDE_DIRS})
target_include_directories(zpg_test PRIVATE ${OPENGL_INCLUDE_DIRS})
target_include_directories(zpg_test PRIVATE ${GLEW_INCLUDE_DIRS})
target_include_directories(zpg_test PRIVATE "/usr/include/stb/")

target_link_libraries(zpg_test OpenGL::GL GLEW::GLEW glfw assimp::assimp)