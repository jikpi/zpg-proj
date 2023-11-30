//
// Created by lvi on 30.11.23.
//

#ifndef ZPG_TEST_ANYGAMELOGIC_H
#define ZPG_TEST_ANYGAMELOGIC_H


#include "../../Managers/EngineResources/ResourcesManager.h"
#include "../../Managers/EngineResources/Map.h"
#include "../../../Shaders/Camera/Camera.h"

class ResourcesManager;
class AnyGameLogic {
protected:
    ResourcesManager *Resources{};
    Map *map{};
    Camera *CameraMain{};

    StandardisedModel *ObjectByCursor(float xCursorCoords, float yCursorCoords, int windowHeight);
    glm::vec3 UnprojectCursor(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth);

public:

    void InitializeResources(ResourcesManager *resources, Map *t_map, Camera *camera);
    virtual ~AnyGameLogic() = default;

    virtual void NextRender() = 0;

    virtual void Reset() = 0;

    virtual void
    MouseCursorClickEvent(float xCursorCoords, float yCursorCoords, int windowHeight, int windowWidth, int button, int action,
                          int mods) = 0;
    virtual void KeyPressEvent(int key, int scancode, int action, int mods) = 0;

    [[nodiscard]] std::string GetMapName() const;
};


#endif //ZPG_TEST_ANYGAMELOGIC_H
