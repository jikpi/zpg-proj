//
// Created by lvi on 1.12.23.
//

#include <iostream>
#include "GameLogic_Overworld.h"

GameLogic_Overworld::GameLogic_Overworld() = default;

void GameLogic_Overworld::NextRender() {
    if (!this->CheckIfCanNextRender()) {
        return;
    }

    //set flashlight to camera location and target
    flashlight->SetPosition(Resources->CameraMain->GetLocation());
    flashlight->SetDirection(Resources->CameraMain->GetTarget() - Resources->CameraMain->GetLocation());
    Resources->ForceRefreshLightsOnCurrentMap();

}

void GameLogic_Overworld::Reset() {
    if (!this->IsInitialized) {
        std::cerr << "ERROR: GameLogic_Overworld: GameLogic is not initialized." << std::endl;
        return;
    }

    flashlight = dynamic_cast<LightSpot *>(map->GetLight("Flashlight").get());


    if (flashlight == nullptr) {
        std::cerr << "ERROR: GameLogic_Overworld: Flashlight is not found." << std::endl;
        return;
    }


    this->IsReady = true;
}

void
GameLogic_Overworld::MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button,
                                           int action, int mods) {

}

void GameLogic_Overworld::KeyPressEvent(int key, int scancode, int action, int mods) {

}
