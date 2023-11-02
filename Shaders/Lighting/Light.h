//
// Created by KOP0269 on 10/20/23.
//

#ifndef ZPG_TEST_LIGHT_H
#define ZPG_TEST_LIGHT_H


#include "glm/vec3.hpp"

class Light {
private:
    glm::vec3 Position{};
    glm::vec3 Color{};
    float Intensity{};

    float Constant;
    float Linear;
    float Quadratic;

public:
    Light(const glm::vec3 &position, const glm::vec3 &color, float intensity);
    explicit Light(const glm::vec3 &position);

    void setPosition(const glm::vec3 &newPosition);
    void setColor(const glm::vec3 &newColor);
    void setIntensity(float newIntensity);
    void setConstant(float newConstant);
    void setLinear(float newLinear);
    void setQuadratic(float newQuadratic);

    [[nodiscard]] const glm::vec3 &getPosition() const;
    [[nodiscard]] const glm::vec3 &getColor() const;
    [[nodiscard]] float getIntensity() const;
    [[nodiscard]] float getConstant() const;
    [[nodiscard]] float getLinear() const;
    [[nodiscard]] float getQuadratic() const;
};


#endif //ZPG_TEST_LIGHT_H
