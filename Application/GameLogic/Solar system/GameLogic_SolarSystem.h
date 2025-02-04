//
// Created by lvi on 1.12.23.
//

#ifndef ZPG_TEST_GAMELOGIC_SOLARSYSTEM_H
#define ZPG_TEST_GAMELOGIC_SOLARSYSTEM_H


#include "../Abstract/AnyGameLogic.h"

class GameLogic_SolarSystem : public AnyGameLogic {
private:
    StandardisedModel *Earth{};

    float moonAngle{};
    StandardisedModel *Moon{};

    void LoadMap();
    bool firstLoad{true};

    void CreateUFOat(glm::vec3 coordinates);
    StandardisedModel* lastUFO{};
    void AddBezierCoordinateToUFO(glm::vec3 coordinates);
public:
    GameLogic_SolarSystem();

    void NextRender() override;
    void Reset() override;
    void MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button,
                               int action, int mods) override;
    void KeyPressEvent(int key, int scancode, int action, int mods) override;

    [[nodiscard]] bool SelfCreatingMap() const override {
        return true;
    }

};


#endif //ZPG_TEST_GAMELOGIC_SOLARSYSTEM_H
