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
public:
    GameLogic_Overworld();
    void NextRender() override;
    void Reset() override;
    void MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button, int action,
                               int mods) override;
    void KeyPressEvent(int key, int scancode, int action, int mods) override;

    [[nodiscard]] bool SelfCreatingMap() const override {
        return false;
    }
};

#endif //ZPG_TEST_GAMELOGIC_OVERWORLD_H
