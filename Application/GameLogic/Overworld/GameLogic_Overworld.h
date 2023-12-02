//
// Created by lvi on 1.12.23.
//

#ifndef ZPG_TEST_GAMELOGIC_OVERWORLD_H
#define ZPG_TEST_GAMELOGIC_OVERWORLD_H


#include "../Abstract/AnyGameLogic.h"
#include "../../../Shaders/Lighting/LightSpot.h"

class GameLogic_Overworld : public AnyGameLogic {
private:
    LightSpot *flashlight{};
    LightPoint *gunLight{};

    void LoadMap();
    bool firstLoad{true};
    int zombieNumber = 15;


    int remainingFrames = 7200;

    void ShotZombie(StandardisedModel *zombie);
    int zombieShot = 0;

    void ShootAnimation();

    bool won = false;
    void WonCondition();

    int currentHorde = 0;
    int maxHorde = 100;
    bool lost = false;
    void LostCondition();

    int defaultGunLightFrames = 1;
    int gunLightFrames = 0;


    int defaultAnimationFrames = 3;
    int animationFrames = 0;
    int nextAnimationTextureIndex = 0;
    StandardisedModel* animatingPlane{};
    std::vector<Texture *> animationTextures;

    StandardisedModel* gunModel{};
    void PortGunToCamera();
public:
    GameLogic_Overworld();
    void NextRender() override;
    void Reset() override;
    void MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button, int action,
                               int mods) override;
    void KeyPressEvent(int key, int scancode, int action, int mods) override;

    [[nodiscard]] bool SelfCreatingMap() const override {
        return true;
    }
};

#endif //ZPG_TEST_GAMELOGIC_OVERWORLD_H
