cmake_minimum_required(VERSION 3.26)
set(GLM_VERSION "0.9.9")

project(zpg_test)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
add_subdirectory(libraries/glm)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

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
        Application/ObjectsManager/Map/Map.cpp
        Application/ObjectsManager/Map/Map.h
        Application/InputHandler/KeyCallbacks/KeyCallbacks.cpp
        Application/InputHandler/KeyCallbacks/KeyCallbacks.h
        Application/DebugErrorMessages/DebugErrorMessages.cpp
        Application/DebugErrorMessages/DebugErrorMessages.h
        Shaders/ShadersCode/LegacyShaderStrings/LegacyShadersStrings.h
        Shaders/ShadersCode/LegacyShaderStrings/LegacyShaderStrings.cpp
        Transformations/Composite/Abstract/Transformation.cpp
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
        Shaders/Camera/CameraObserver/CameraObserver.cpp
        Shaders/Camera/CameraObserver/CameraObserver.h
        Application/Configuration/AGlobalConfig.h
        Application/Configuration/AGlobalConfig.cpp
        Shaders/ShadersCode/Loader/ShaderFileLoader.cpp
        Shaders/ShadersCode/Loader/ShaderFileLoader.h
        Shaders/Lighting/Light.cpp
        Shaders/Lighting/Light.h
        Application/ObjectsManager/ShaderLinking/MapToShaderLinker.cpp
        Application/ObjectsManager/ShaderLinking/MapToShaderLinker.h
        Application/ObjectsManager/ShaderLinking/ShaderObjectSet/ShaderObjectSet.cpp
        Application/ObjectsManager/ShaderLinking/ShaderObjectSet/ShaderObjectSet.h
        Shaders/ShaderType.h
        Model/Material.cpp
        Model/Material.h
        Model/Abstract/RenderableObject.cpp
        Model/Abstract/RenderableObject.h
        Shaders/ShaderProgram/ShaderHandlerFactory/ShaderHandlerFactory.cpp
        Shaders/ShaderProgram/ShaderHandlerFactory/ShaderHandlerFactory.h
        Shaders/Lighting/Uniforms/LightsArrayPointUniform.cpp
        Shaders/Lighting/Uniforms/LightsArrayPointUniform.h
        Shaders/ShaderProgram/ShaderBase/ShaderBase.cpp
        Shaders/ShaderProgram/ShaderBase/ShaderBase.h
        Application/ObjectsManager/Map/MapManager.cpp
        Application/ObjectsManager/Map/MapManager.h
        Application/ObjectsManager/Map/PremadeMaps/PremadeMapsFactory.cpp
        Application/ObjectsManager/Map/PremadeMaps/PremadeMapsFactory.h
        ExtResources/LessonResources/InclLessonModels.h
)
target_link_libraries(zpg_test ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} glfw glm::glm)