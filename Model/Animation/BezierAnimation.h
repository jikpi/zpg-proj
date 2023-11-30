//
// Created by lvi on 30.11.23.
//

#ifndef ZPG_TEST_BEZIERANIMATION_H
#define ZPG_TEST_BEZIERANIMATION_H


#include <vector>
#include "Abstract/AnyAnimation.h"

class BezierAnimation : public AnyAnimation {
private:
    std::vector<glm::vec3> Points;

    static glm::vec3 CalculateBezierCubic(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

    float tArg;

    bool tBackwards;
    float smoothTDiff;
    void NextStep();
public:
    explicit BezierAnimation(float tChange);
    ~BezierAnimation() override = default;

    enum class BezierAnimationStyle {
        Snap,
        RoundAround,
        SmoothRoundAround,
    };

    BezierAnimationStyle Style;

    void DoAnimation(float t) override;

    void AddPoint(glm::vec3 point);
    void ClearPoints();


    void SetStyle(BezierAnimationStyle newStyle);
    void SetSmoothTDiff(float newSmoothTDiff);

    [[nodiscard]] std::shared_ptr<Transformation> GetResult() const override;
};


#endif //ZPG_TEST_BEZIERANIMATION_H
