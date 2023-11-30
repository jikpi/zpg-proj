//
// Created by lvi on 30.11.23.
//

#ifndef ZPG_TEST_ANYGAMELOGIC_H
#define ZPG_TEST_ANYGAMELOGIC_H


#include "../../Managers/Map/ResourcesManager.h"

class AnyGameLogic {
private:
    ResourcesManager Resources;
    Map* map;

public:
    AnyGameLogic();
    virtual ~AnyGameLogic() = default;

    virtual void NextRender() = 0;

    virtual void Reset() = 0;
    virtual void ObjectClicked(int contextID) = 0;


};


#endif //ZPG_TEST_ANYGAMELOGIC_H
