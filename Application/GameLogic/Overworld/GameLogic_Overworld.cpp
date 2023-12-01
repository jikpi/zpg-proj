//
// Created by lvi on 1.12.23.
//

#include <iostream>
#include "GameLogic_Overworld.h"
#include "../../../Shaders/Lighting/LightDirectional.h"
#include "../../../Transformations/Composite/Factory/TransformationFactory.h"

GameLogic_Overworld::GameLogic_Overworld() = default;

void GameLogic_Overworld::NextRender() {
    if (!this->CheckIfCanNextRender()) {
        return;
    }

    //set flashlight to camera location and target
    flashlight->SetPosition(Resources->CameraMain->GetLocation());
    flashlight->SetDirection(Resources->CameraMain->GetTarget() - Resources->CameraMain->GetLocation());
    Resources->ForceRefreshLightsOnCurrentMap();

    //gun light
    if (gunLightFrames > 0) {
        gunLightFrames--;
    } else {
        gunLight->SetColor(glm::vec3(0.0f, 0.0f, 0.0f));
    }

    if (!lost && !won) {
        //decrease remaining frames
        if (remainingFrames > 0) {
            remainingFrames--;

            if (remainingFrames % 600 == 0) {
                std::cout << "Remaining time: " << remainingFrames << std::endl;

            }

        } else {
            LostCondition();
        }
    }


    if (lost) {

        if (currentHorde > maxHorde) {
            return;
        }
        currentHorde++;

        ShaderHandler *PhongTextureShader = SelectShader(Resources->Shaders, "PhongTexture");
        std::string name = "Zombie any";
        float x = (rand() % 50) - 25;
        float z = (rand() % 50) - 25;
        float rotation = (rand() % 360);

        std::shared_ptr<StandardisedModel> zombie = Resources->ModelObjectController.UseAny("Lesson/zombie.obj", name);
        zombie->SetShaderProgram(PhongTextureShader);
        zombie->SetTexture(Resources->TextureObjectsController.UseTexture("Lesson/zombie.png"));
        zombie->InsertTransfMove(glm::vec3(x, -1.0f, z))
                .InsertTransfRotate(rotation, glm::vec3(0, rotation, 0))
                .ConsolidateTransf();
        zombie->SetMaterial(Material());
        Resources->AddObjectToMap(map, zombie);

        zombie->InsertTransfComposite(TransformationFactory::CreateOrbit(glm::vec3(x, -1.0f, z),
                                                                         0.03f,
                                                                         glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    if(won) {
        if (animationFrames > 0) {
            animationFrames--;
        } else {
            animationFrames = defaultAnimationFrames;
            animatingPlane->SetTexture(animationTextures.at(nextAnimationTextureIndex));
            nextAnimationTextureIndex++;
            if(nextAnimationTextureIndex >= animationTextures.size()) {
                nextAnimationTextureIndex = 0;
            }
        }
    }

}

void GameLogic_Overworld::Reset() {
    if (!this->IsInitialized) {
        std::cerr << "ERROR: GameLogic_Overworld: GameLogic is not initialized." << std::endl;
        return;
    }

    if (this->firstLoad) {
        this->firstLoad = false;
        this->LoadMap();
    }


//    flashlight = dynamic_cast<LightSpot *>(map->GetLight("Flashlight").get());


    if (flashlight == nullptr) {
        std::cerr << "ERROR: GameLogic_Overworld: Flashlight is not found." << std::endl;
        return;
    }


    this->IsReady = true;
}

void GameLogic_Overworld::LostCondition() {
    if (won) {
        return;
    }

    this->lost = true;
    std::cout << "You lost!" << std::endl;

    std::shared_ptr<LightDirectional> directionalLight = std::make_shared<LightDirectional>(
            glm::vec3(0.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, 0.0f, 0.0f));


    Resources->AddLightToMap(map, directionalLight);


}

void GameLogic_Overworld::WonCondition() {
    if (lost) {
        return;
    }

    //Switch to day
    std::shared_ptr<LightDirectional> directionalLight = std::make_shared<LightDirectional>(
            glm::vec3(0.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f));
    directionalLight->SetColor(glm::vec3(0.9f, 0.9f, 0.9f));
    Resources->AddLightToMap(map, directionalLight);
    std::shared_ptr<StandardisedModel> starSkybox = Resources->ModelObjectController.UsePosition("skybox.obj", "Sky");
    ShaderHandler *SkyboxShader = SelectShader(Resources->Shaders, "Skybox");
    starSkybox->SetShaderProgram(SkyboxShader);
    Texture *starSkyboxTexture = Resources->TextureObjectsController.UseCubemap("Lesson/FieldSkybox/field");
    starSkybox->SetTexture(starSkyboxTexture);
    Resources->AddSkyboxToMap(map, starSkybox);

    //Display trophy

    std::shared_ptr<StandardisedModel> trophy = Resources->ModelObjectController.UseAny("WinnerCup.obj", "Trophy");
    trophy->SetShaderProgram(SelectShader(Resources->Shaders, "Phong"));
    trophy->InsertTransfMove(glm::vec3(10, 2, -20))
            .InsertTransfScale(glm::vec3(0.005f, 0.005f, 0.005f))
            .ConsolidateTransf();

    //rotate it
    trophy->InsertTransfRotate(1.0f, glm::vec3(0, 1, 0));

    //golden material
    Material gold = Material(glm::vec3(0.1f, 0.1f, 0.1f),
                             glm::vec3(1.0f, 1.0f, 0.1f),
                             glm::vec3(0.5f, 0.5f, 0.5f),
                             255.0f);

    trophy->SetMaterial(gold);
    for (auto &mesh: trophy->ChildObjects) {
        mesh->SetMaterial(gold);
    }

    Resources->AddObjectToMap(map, trophy);


    //add plane next to trophy
    std::shared_ptr<StandardisedModel> newAnimatingPlane = Resources->ModelObjectController.UseAny("Lesson/planeSingleTex.obj", "Heye");
    newAnimatingPlane->SetShaderProgram(SelectShader(Resources->Shaders, "PhongTexture"));
    newAnimatingPlane->SetTexture(animationTextures.at(0));
    newAnimatingPlane->InsertTransfMove(glm::vec3(10, 0, -20))
            .InsertTransfScale(glm::vec3(0.5f, 0.5f, 0.5f)).InsertTransfRotate(90, glm::vec3(1, 0, 0))
            .ConsolidateTransf();
    Resources->AddObjectToMap(map, newAnimatingPlane);
    animatingPlane = newAnimatingPlane.get();


    //put camera to trophy
    Resources->CameraMain->SetLocation(glm::vec3(10, 1, -15));
    Resources->CameraMain->SetTarget(glm::vec3(10, 2, -20) + glm::vec3(0, 0, 1));


}

void GameLogic_Overworld::ShotZombie(StandardisedModel *zombie) {
    std::cout << "Zombie shot " << ++zombieShot << " of " << zombieNumber << std::endl;
    zombie->SetMaterial(Material(glm::vec3(0.1f, 0.1f, 0.1f),
                                 glm::vec3(1.0f, 0.5f, 0.5f),
                                 glm::vec3(0.5f, 0.5f, 0.5f),
                                 32.0f));

    zombie->InsertTransfRotate(90, glm::vec3(1, 0, 0)).InsertTransfRotate(90, glm::vec3(0, 1, 0))
            .InsertTransfMove(glm::vec3(0, 0, -0.5f))
            .ConsolidateTransf();

    if (zombieShot == zombieNumber) {
        std::cout << "You won!" << std::endl;
        won = true;
        WonCondition();
    }
}


void
GameLogic_Overworld::MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button,
                                           int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        //jerk camera up
        Resources->CameraMain->LookSphericalVertical(1.5f);

        //enable gun light
        gunLightFrames = defaultGunLightFrames;
        gunLight->SetColor(glm::vec3( 1.0f, 1.0f, 0.0f));
        gunLight->SetPosition(Resources->CameraMain->GetLocation());


        StandardisedModel *model = AnyGameLogic::ObjectByCenter(windowHeight, windowWidth);
        if (model == nullptr) {
            return;
        }

        if (model->Name().find("Zombie") == 0) {
            ShotZombie(model);
        }

    }

//    //force win with right click
//    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
//        won = true;
//        WonCondition();
//    }

}

void GameLogic_Overworld::KeyPressEvent(int key, int scancode, int action, int mods) {

}
