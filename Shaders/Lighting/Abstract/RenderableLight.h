//
// Created by KOP0269 on 11/2/23.
//

#ifndef ZPG_TEST_RENDERABLELIGHT_H
#define ZPG_TEST_RENDERABLELIGHT_H


#include "glm/vec3.hpp"
#include "LightType.h"

class RenderableLight {
private:
    static void PrintFalseImplementation_LightPoint();
    static void PrintFalseImplementation_LightDirectional();
    static void PrintFalseImplementation_LightSpot();
protected:
    glm::vec3 Color{};
    float Intensity{};

    LightType Type;
public:
    RenderableLight(LightType type, const glm::vec3 &color, float intensity);
    explicit RenderableLight(LightType type, const glm::vec3 &color);
    explicit RenderableLight(LightType type, float intensity);
    explicit RenderableLight(LightType type);
    RenderableLight();
    virtual ~RenderableLight() = default;

    [[nodiscard]] const glm::vec3 &GetColor() const;
    [[nodiscard]] float GetIntensity() const;
    [[nodiscard]] LightType GetType() const;

    void SetColor(const glm::vec3 &newColor);
    void SetIntensity(float newIntensity);

    //Virtual member methods
    //Point light
    virtual void SetPosition(const glm::vec3 &newPosition);
    [[nodiscard]] virtual const glm::vec3 &GetPosition() const;
    virtual void SetConstant(float newConstant);
    [[nodiscard]] virtual float GetConstant() const;
    virtual void SetLinear(float newLinear);
    [[nodiscard]] virtual float GetLinear() const;
    virtual void SetQuadratic(float newQuadratic);
    [[nodiscard]] virtual float GetQuadratic() const;
    //Directional light
    virtual void SetDirection(const glm::vec3 &newDirection);
    [[nodiscard]] virtual const glm::vec3 &GetDirection() const;
    //Spot light
};


#endif //ZPG_TEST_RENDERABLELIGHT_H
