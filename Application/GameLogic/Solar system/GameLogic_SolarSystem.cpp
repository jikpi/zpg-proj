//
// Created by lvi on 1.12.23.
//

#include <iostream>
#include "GameLogic_SolarSystem.h"
#include "../../../Transformations/Composite/Factory/TransformationFactory.h"
#include "../../../Model/Animation/BezierAnimation.h"

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
    if (!this->IsInitialized) {
        std::cerr << "ERROR: GameLogic_SolarSystem: GameLogic is not initialized." << std::endl;
        return;
    }

    if (this->firstLoad) {
        this->firstLoad = false;
        this->LoadMap();
    }


    Earth = AnyGameLogic::map->GetObject("Earth").get();
    Moon = AnyGameLogic::map->GetObject("Moon").get();
    moonAngle = 0.0f;

    if (Earth == nullptr || Moon == nullptr) {
        std::cerr << "ERROR: GameLogic_SolarSystem: Earth or Moon is null." << std::endl;
        return;
    }

    this->IsReady = true;
}

void GameLogic_SolarSystem::AddBezierCoordinateToUFO(glm::vec3 coordinates) {
    if (lastUFO == nullptr) {
        return;
    }

    std::unique_ptr<AnyAnimation> &animation = lastUFO->Animations.at(0);
    auto *bezierAnim = dynamic_cast<BezierAnimation *>(animation.get());
    bezierAnim->AddPoint(coordinates);

    if (bezierAnim->GetPointsCount() == 4) {
        lastUFO->ClearTransf();
        lastUFO->ResetTransf();
        lastUFO->InsertTransfScale(glm::vec3(0.05f, 0.05f, 0.05f)).ConsolidateTransf();
    }
}

void GameLogic_SolarSystem::CreateUFOat(glm::vec3 coordinates) {
    std::shared_ptr<StandardisedModel> objectUFO = Resources->ModelObjectController.UseAny("UFO2.obj",
                                                                                           "UFO");
    objectUFO->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                    glm::vec3(1.0f, 0.5f, 0.0f),
                                    glm::vec3(1.0f, 0.5f, 0.0f),
                                    32.0f));
    objectUFO->SetShaderProgram(SelectShader(Resources->Shaders, "Phong"));

    objectUFO->InsertTransfMove(coordinates).InsertTransfScale(glm::vec3(0.05f, 0.05f, 0.05f))
            .ConsolidateTransf();
    Resources->AddObjectToMap(map, objectUFO);

    std::unique_ptr<AnyAnimation> animation1 = std::make_unique<BezierAnimation>(0.001f);
    auto *bezierAnim = dynamic_cast<BezierAnimation *>(animation1.get());
    bezierAnim->SetStyle(BezierAnimation::BezierAnimationStyle::RoundAround);

    bezierAnim->AddPoint(coordinates);
    objectUFO->InsertAnimation(std::move(animation1));


    lastUFO = objectUFO.get();
}


void
GameLogic_SolarSystem::MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button,
                                             int action, int mods) {
    if (button == 0 && action == 1) {
        glm::vec3 unprojectedCoords = AnyGameLogic::UnprojectCursor(xCursorCoords, yCursorCoords, windowHeight, windowWidth);
        this->CreateUFOat(unprojectedCoords);
    }

    if (button == 1 && action == 1) {
        glm::vec3 unprojectedCoords = AnyGameLogic::UnprojectCursor(xCursorCoords, yCursorCoords, windowHeight, windowWidth);
        this->AddBezierCoordinateToUFO(unprojectedCoords);
    }
}

void GameLogic_SolarSystem::KeyPressEvent(int key, int scancode, int action, int mods) {

}