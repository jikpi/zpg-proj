//
// Created by lvi on 1.12.23.
//

#include <iostream>
#include "GameLogic_4Spheres.h"

GameLogic_4Spheres::GameLogic_4Spheres() = default;

void GameLogic_4Spheres::Reset() {
    if(!this->IsInitialized)
    {
        std::cerr << "ERROR: GameLogic_4Spheres: GameLogic is not initialized." << std::endl;
        return;
    }

    if(this->firstLoad)
    {
        this->firstLoad = false;
        this->LoadMap();
    }



    this->IsReady = true;
}

void GameLogic_4Spheres::NextRender() {
    if (!this->CheckIfCanNextRender()) {
        return;
    }


}

void GameLogic_4Spheres::MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button,
                                               int action, int mods) {

}

void GameLogic_4Spheres::KeyPressEvent(int key, int scancode, int action, int mods) {

}
