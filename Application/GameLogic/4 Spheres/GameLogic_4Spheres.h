//
// Created by lvi on 1.12.23.
//

#ifndef ZPG_TEST_GAMELOGIC_4SPHERES_H
#define ZPG_TEST_GAMELOGIC_4SPHERES_H


#include "../Abstract/AnyGameLogic.h"

class GameLogic_4Spheres : public AnyGameLogic {
private:

    void LoadMap();
    bool firstLoad{true};
public:
    GameLogic_4Spheres();
    void Reset() override;
    void NextRender() override;
    void MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button, int action, int mods) override;
    void KeyPressEvent(int key, int scancode, int action, int mods) override;


    [[nodiscard]] bool SelfCreatingMap() const override
    {
        return true;
    };
};


#endif //ZPG_TEST_GAMELOGIC_4SPHERES_H
