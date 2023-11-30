//
// Created by lvi on 30.11.23.
//

#ifndef ZPG_TEST_ANYANIMATION_H
#define ZPG_TEST_ANYANIMATION_H


#include <glm/vec3.hpp>
#include <memory>
#include "../../../Transformations/Composite/Abstract/Transformation.h"

class AnyAnimation {
protected:
    glm::vec3 Result = glm::vec3(0);
    float tChange;
public:
    explicit AnyAnimation(float tChange);
    virtual ~AnyAnimation() = default;
    virtual void DoAnimation(float t) = 0;
    bool Enabled = true;

    void SetTChange(float new_tChange);
    [[nodiscard]] virtual std::shared_ptr<Transformation> GetResult() const = 0;
};


#endif //ZPG_TEST_ANYANIMATION_H
