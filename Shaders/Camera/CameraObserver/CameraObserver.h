//
// Created by KOP0269 on 10/14/23.
//

#ifndef ZPG_TEST_CAMERAOBSERVER_H
#define ZPG_TEST_CAMERAOBSERVER_H


#include "glm/ext/matrix_float4x4.hpp"

class CameraObserver {
public:
    virtual ~CameraObserver() = default;
    virtual void CameraChangedNotification(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix,
                                           const glm::vec3 &cameraLocation) = 0;
};


#endif //ZPG_TEST_CAMERAOBSERVER_H
