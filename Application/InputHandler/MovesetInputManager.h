//
// Created by KOP0269 on 10/14/23.
//

#ifndef ZPG_TEST_MOVESETINPUTMANAGER_H
#define ZPG_TEST_MOVESETINPUTMANAGER_H


//#include "../Engine.h"

#include <memory>

class MovesetInputManager : public std::enable_shared_from_this<MovesetInputManager> {
private:

    bool StandStill{};
    bool MovingForward{};
    bool MovingSide{};

    float CurrentForwardVelocity{};
    float CurrentSideVelocity{};
    float CurrentVerticalVelocity{};

    float MaxForwardVelocity{};
    float MaxSideVelocity{};
    float MaxVerticalVelocity{};

    float Acceleration{};

    void UpdateMovingForward(bool isMoving);
    void UpdateMovingSide(bool isMoving);

public:
    explicit MovesetInputManager();

    void Register();

    void CallbackKey(int key, int scancode, int action, int mods);

    bool IsStandStill() const;
    float ReadForward() const;
    float ReadSide() const;
    float ReadVertical() const;
};


#endif //ZPG_TEST_MOVESETINPUTMANAGER_H
