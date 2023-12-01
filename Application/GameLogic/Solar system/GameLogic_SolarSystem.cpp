//
// Created by lvi on 1.12.23.
//

#include <iostream>
#include "GameLogic_SolarSystem.h"

GameLogic_SolarSystem::GameLogic_SolarSystem() = default;


void GameLogic_SolarSystem::NextRender() {
    if (!this->CheckIfCanNextRender()) {
        return;
    }

}

void GameLogic_SolarSystem::Reset() {
    this->IsReady = true;
}


void
GameLogic_SolarSystem::MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button,
                                             int action, int mods) {

}

void GameLogic_SolarSystem::KeyPressEvent(int key, int scancode, int action, int mods) {

}
