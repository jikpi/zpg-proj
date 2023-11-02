//
// Created by KOP0269 on 10/14/23.
//

#include "MovesetInputManager.h"
#include "KeyCallbacks/KeyCallbacks.h"

#include <utility>

MovesetInputManager::MovesetInputManager() : CurrentForwardVelocity(0),
                                             CurrentSideVelocity(0),
                                             CurrentVerticalVelocity(0),

                                             MaxForwardVelocity(0.04f),
                                             MaxSideVelocity(0.04f),
                                             MaxVerticalVelocity(0.04f),

                                             StandStill(true),
                                             MovingForward(false),
                                             MovingSide(false) {
}

void MovesetInputManager::Register() {
    KeyCallbacks::MovesetManager = shared_from_this();
}


void MovesetInputManager::CallbackKey(int key, int scancode, int action, int mods) {

    switch (action) {
        case GLFW_REPEAT:
        case GLFW_PRESS:
            switch (key) {
                case GLFW_KEY_W:
                    CurrentForwardVelocity = MaxForwardVelocity;
                    break;
                case GLFW_KEY_S:
                    CurrentForwardVelocity = -MaxForwardVelocity;
                    break;

                case GLFW_KEY_A:
                    CurrentSideVelocity = MaxSideVelocity;
                    break;
                case GLFW_KEY_D:
                    CurrentSideVelocity = -MaxSideVelocity;
                    break;

                case GLFW_KEY_R:
                    CurrentVerticalVelocity = MaxVerticalVelocity;

                    break;
                case GLFW_KEY_F:
                    CurrentVerticalVelocity = -MaxVerticalVelocity;
                    break;
                default:
                    break;
            }
            break;
        case GLFW_RELEASE:
            switch (key) {
                case GLFW_KEY_W:
                    CurrentForwardVelocity = 0;
                    break;
                case GLFW_KEY_S:
                    CurrentForwardVelocity = 0;
                    break;

                case GLFW_KEY_A:
                    CurrentSideVelocity = 0;
                    break;
                case GLFW_KEY_D:
                    CurrentSideVelocity = 0;
                    break;

                case GLFW_KEY_R:
                    CurrentVerticalVelocity = 0;
                    break;
                case GLFW_KEY_F:
                    CurrentVerticalVelocity = 0;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    if (CurrentForwardVelocity == 0 && CurrentSideVelocity == 0 && CurrentVerticalVelocity == 0) {
        StandStill = true;
    } else {
        StandStill = false;
    }
}

float MovesetInputManager::ReadForward() const {
    return CurrentForwardVelocity;
}

float MovesetInputManager::ReadSide() const {
    return CurrentSideVelocity;
}

float MovesetInputManager::ReadVertical() const {
    return CurrentVerticalVelocity;
}

bool MovesetInputManager::IsStandStill() const {
    return StandStill;
}

void MovesetInputManager::UpdateMovingForward(bool isMoving) {
    MovingForward = isMoving;
}

void MovesetInputManager::UpdateMovingSide(bool isMoving) {
    MovingSide = isMoving;
}
