//
// Created by KOP0269 on 10/9/23.
//

#include <iostream>
#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera(float alpha, float fi, float fov, float aspectRatio,
               float minRender, float maxRender) :
        HasViewChanged(true),
        ViewMatrix(glm::mat4(1.0f)),
        ProjectionMatrix(glm::perspective(fov, aspectRatio, minRender, maxRender)),
        IsPerspective(true),
        FollowYDirection(false),
        IsUnlocked(false),

        Alpha(alpha),
        Fi(fi),

        FOV(fov),
        AspectRatio(aspectRatio),
        MinRender(minRender),
        MaxRender(maxRender),

        DefaultLocation(glm::vec3(0.0f, 0.0f, 5.0f)),
        DefaultTarget(glm::vec3(0.0f, 0.0f, 0.0f)),
        DefaultUp(glm::vec3(0.0f, 1.0f, 0.0f)) {


    Location = DefaultLocation;
    Up = DefaultUp;
    Target = DefaultTarget;

    GetViewMatrix();
}

void Camera::CheckNans() const {
    if (std::isnan(Location.x) || std::isnan(Location.y) || std::isnan(Location.z)) {
        std::throw_with_nested(std::runtime_error("'Location' collapsed"));
    }

    if (std::isnan(Target.x) || std::isnan(Target.y) || std::isnan(Target.z)) {
        std::throw_with_nested(std::runtime_error("'Target' collapsed"));
    }
}

void Camera::CalculateViewMatrix() {
    if (IsUnlocked) {
        return;
    }

    CalculateTargetSphericalCoords();
    ViewMatrix = glm::lookAt(Location, Target, Up);
    this->CheckNans();
    HasViewChanged = false;
}

void Camera::CalculateProjectionMatrix() {
    if (IsPerspective) {
        ProjectionMatrix = glm::perspective(FOV, AspectRatio, MinRender, MaxRender);
    } else {
        float height = 6.0f;
        float half_width = 0.5f * AspectRatio * height;
        ProjectionMatrix = glm::ortho(-half_width, half_width, -3.0f, 3.0f, MinRender, MaxRender);
    }
}


void Camera::SetAspectRatio(float aspectRatio) {
    this->AspectRatio = aspectRatio;
    this->CalculateProjectionMatrix();
}

void Camera::Reset() {
    Location = DefaultLocation;
    Up = DefaultUp;

    Alpha = 1;
    Fi = 1;
    CalculateTargetSphericalCoords();

    this->CameraChanged();
}

void Camera::SetLocation(glm::vec3 newLocation) {
    this->Location = newLocation;
    this->CameraChanged();
}

void Camera::SetTarget(glm::vec3 newTarget) {
    this->Target = newTarget;
    this->CameraChanged();
}

void Camera::SetUp(glm::vec3 newUp) {
    this->Up = newUp;
    this->CameraChanged();
}

glm::mat4 Camera::GetProjectionMatrix() {
    return ProjectionMatrix;
}

glm::mat4 Camera::GetViewMatrix() {
    if (HasViewChanged) {
        CalculateViewMatrix();

        CheckNans();
    }

    return ViewMatrix;
}

void Camera::CalculateTargetSphericalCoords() {
    Target.x = sin(Alpha) * cos(Fi);
    Target.z = sin(Alpha) * sin(Fi);
    Target.y = cos(Alpha);

    Target += Location;
}

void Camera::ChangeAlpha(float change) {
    Alpha += change;
    Alpha = glm::clamp(Alpha, glm::radians(1.0f), glm::pi<float>() - glm::radians(1.0f));
    this->CameraChanged();
}

void Camera::ChangeFi(float change) {
    Fi += change;
    this->CameraChanged();
}

void Camera::LookSphericalSide(float degrees) {
    if(IsUnlocked)
    {
        return;
    }
    ChangeFi(glm::radians(degrees));
}

void Camera::LookSphericalVertical(float degrees) {
    if(IsUnlocked)
    {
        return;
    }

    ChangeAlpha(-glm::radians(degrees));
}

void Camera::MoveForwardBackward(float distance) {
    if(IsUnlocked)
    {
        return;
    }

    //calculate direction, normalize to 1
    glm::vec3 direction = glm::normalize(Target - Location);

    //if the camera should follow where it's looking
    if (!FollowYDirection) {
        direction.y = 0;
        //normalize so that the camera moves at the same speed
        direction = glm::normalize(direction);
    }

    //update location
    Location += direction * distance;

    //note the update
    this->CameraChanged();
}

void Camera::MoveSideToSide(float distance) {
    if(IsUnlocked)
    {
        return;
    }

    //calculate direction, normalize to 1
    glm::vec3 forward = glm::normalize(Target - Location);

    //get vector that is perpendicular to forward and up
    glm::vec3 right = glm::normalize(glm::cross(forward, Up));

    //update location and target
    Location -= right * distance;
    Target -= right * distance;

    //note the update
    this->CameraChanged();
}

void Camera::MoveUpDown(float distance) {
    if(IsUnlocked)
    {
        return;
    }

    Location += Up * distance;
    Target += Up * distance;

    this->CameraChanged();
}

void Camera::RegisterCameraObserver(const std::shared_ptr<CameraObserver> &observer) {
    CameraObservers.push_back(observer);
}

void Camera::NotifyShaderProgramObservers() {
    this->CalculateViewMatrix();

    for (auto &observer: CameraObservers) {
        if (auto observerPtr = observer.lock()) {
            observerPtr->CameraChangedNotification(this->ViewMatrix, this->ProjectionMatrix, this->Location);
        }
    }
}

void Camera::CameraChanged() {
    HasViewChanged = true;
    NotifyShaderProgramObservers();
}

void Camera::UnlockSet(bool lock) {
    IsUnlocked = lock;
}

bool Camera::UnlockState() const {
    return IsUnlocked;
}

void Camera::SetPerspectiveProjection(bool state) {
    IsPerspective = state;
    this->CalculateProjectionMatrix();
}

void Camera::SetFollowYDirection(bool state) {
    FollowYDirection = state;
}

bool Camera::GetPerspectiveProjection() const {
    return IsPerspective;
}

bool Camera::GetFollowYDirection() const {
    return FollowYDirection;
}

glm::vec3 Camera::GetLocation() const {
    return Location;
}

glm::vec3 Camera::GetTarget() const {
    return Target;
}





