//
// Created by KOP0269 on 10/9/23.
//

#ifndef ZPG_TEST_CAMERA_H
#define ZPG_TEST_CAMERA_H


#include <memory>
#include "../GLSLShader.h"
#include "../ShaderProgram/ShaderHandler.h"
#include "CameraObserver/CameraObserver.h"
#include "../../Application/Configuration/AGlobalConfig.h"
#include "glm/trigonometric.hpp"

class ShaderHandler;

class Camera {
private:
    std::vector<std::weak_ptr<CameraObserver>> CameraObservers;

    float FOV;
    float AspectRatio;
    float MinRender;
    float MaxRender;

    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;

    glm::vec3 DefaultLocation{};
    glm::vec3 DefaultTarget{};
    glm::vec3 DefaultUp{};

    glm::vec3 Location{};
    glm::vec3 Target{};
    glm::vec3 Up{};

    float Alpha;
    float Fi;

    bool HasViewChanged;

    bool IsUnlocked;

    bool IsPerspective;

    bool FollowYDirection;

    void NotifyShaderProgramObservers();

    void CalculateViewMatrix();
    void CalculateProjectionMatrix();

    void ChangeAlpha(float change);
    void ChangeFi(float change);
    void CalculateTargetSphericalCoords();


    void CameraChanged();

    void CheckNans() const;
public:
    explicit Camera(float alpha = 1.5f, float fi = -1.5f, float fov = glm::radians(DEF_CAMERA_FOV),
                    float aspectRatio = DEF_CAMERA_ASPECTRATIO, float minRender = DEF_CAMERA_MINRENDER, float maxRender = DEF_CAMERA_MAXRENDER);

    void RegisterCameraObserver(const std::shared_ptr<CameraObserver> &observer);

    void SetAspectRatio(float aspectRatio);

    void SetLocation(glm::vec3 newLocation);
    void SetTarget(glm::vec3 newTarget);
    void SetUp(glm::vec3 newUp);

    [[nodiscard]] glm::vec3 GetLocation() const;
    [[nodiscard]] glm::vec3 GetTarget() const;

    void LookSphericalSide(float degrees);
    void LookSphericalVertical(float degrees);

    void MoveForwardBackward(float distance);
    void MoveSideToSide(float distance);
    void MoveUpDown(float distance);

    void Reset();
    void UnlockSet(bool lock);
    [[nodiscard]] bool UnlockState() const;

    [[nodiscard]] bool GetPerspectiveProjection() const;
    void SetPerspectiveProjection(bool state);
    [[nodiscard]] bool GetFollowYDirection() const;
    void SetFollowYDirection(bool state);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
};


#endif //ZPG_TEST_CAMERA_H
