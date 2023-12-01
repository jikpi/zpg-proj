//
// Created by lvi on 1.12.23.
//

#include <iostream>
#include "GameLogic_SolarSystem.h"
#include "../../../Transformations/Composite/Factory/TransformationFactory.h"

GameLogic_SolarSystem::GameLogic_SolarSystem() = default;


void GameLogic_SolarSystem::NextRender() {
    if (!this->CheckIfCanNextRender()) {
        return;
    }

    //Animate moon orbiting Earth
    Moon->SetTransf(Earth->GetTransf());
    Moon->InsertTransfScale(glm::vec3(0.1f, 0.1f, 0.1f));
    Moon->InsertTransfRotate(moonAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    Moon->InsertTransfMove(glm::vec3(20.0f, 0.0f, 0.0f));
    Moon->ConsolidateTransf();
    moonAngle += 1.1f;
    if (moonAngle > 360.0f) {
        moonAngle = 0.0f;
    }

}

void GameLogic_SolarSystem::Reset() {
    if(!this->IsInitialized)
    {
        std::cerr << "ERROR: GameLogic_SolarSystem: GameLogic is not initialized." << std::endl;
        return;
    }

    if(this->firstLoad)
    {
        this->firstLoad = false;
        this->LoadMap();
    }



    Earth = AnyGameLogic::map->GetObject("Earth").get();
    Moon = AnyGameLogic::map->GetObject("Moon").get();
    moonAngle = 0.0f;

    if(Earth == nullptr || Moon == nullptr)
    {
        std::cerr << "ERROR: GameLogic_SolarSystem: Earth or Moon is null." << std::endl;
        return;
    }

    this->IsReady = true;
}


void
GameLogic_SolarSystem::MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button,
                                             int action, int mods) {

}

void GameLogic_SolarSystem::KeyPressEvent(int key, int scancode, int action, int mods) {

}