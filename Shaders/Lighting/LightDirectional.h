//
// Created by KOP0269 on 11/2/23.
//

#ifndef ZPG_TEST_LIGHTDIRECTIONAL_H
#define ZPG_TEST_LIGHTDIRECTIONAL_H


#include "Abstract/RenderableLight.h"

class LightDirectional : public RenderableLight {
private:
    glm::vec3 Direction{};
public:
    LightDirectional(const glm::vec3 &direction, const glm::vec3 &color, float intensity);
    LightDirectional(const glm::vec3 &direction, const glm::vec3 &color);
    explicit LightDirectional(const glm::vec3 &direction);
    LightDirectional();

    [[nodiscard]] const glm::vec3 &GetDirection() const override;
    void SetDirection(const glm::vec3 &newDirection) override;

};


#endif //ZPG_TEST_LIGHTDIRECTIONAL_H
