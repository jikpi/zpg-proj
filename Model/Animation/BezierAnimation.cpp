//
// Created by lvi on 30.11.23.
//

#include <glm/ext/scalar_constants.hpp>
#include <cmath>
#include <iostream>
#include "BezierAnimation.h"
#include "../../Transformations/Composite/Transformations/Move.h"
#include "../../Application/Configuration/AGlobalConfig.h"

BezierAnimation::BezierAnimation(float tChange) : tArg(0),
                                                  Points(),
                                                  Style(BezierAnimationStyle::Snap),
                                                  tBackwards(false),
                                                  smoothTDiff(DEF_ANIMATION_BEZIER_SMOOTH_T_DIFF),
                                                  AnyAnimation(tChange) {
}

glm::vec3 BezierAnimation::CalculateBezierCubic(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    glm::vec3 p = uuu * p0; //first term
    p += 3 * uu * t * p1; //second term
    p += 3 * u * tt * p2; //third term
    p += ttt * p3; //fourth term

    return p;
}

void BezierAnimation::NextStep() {
    switch (Style) {
        case BezierAnimationStyle::Snap:
            if (tArg > 1) {
                tArg = 0;
            } else {
                tArg += tChange;
            }
            break;
        case BezierAnimationStyle::RoundAround:
            if (tBackwards) {
                tArg -= tChange;
                if (tArg <= 0) {
                    tArg = 0;
                    tBackwards = false;
                }
            } else {
                tArg += tChange;
                if (tArg >= 1) {
                    tArg = 1;
                    tBackwards = true;
                }
            }
            break;
        case BezierAnimationStyle::SmoothRoundAround:
            float adjustedTChange = tChange;

            const float minTChange = 0.1f;
            // Apply smoothing
            if (tArg < smoothTDiff) {
                // -> t=0
                adjustedTChange = std::max(minTChange, (std::sin(glm::pi<float>() * tArg / (2.0f * smoothTDiff))) * tChange);
            } else if (tArg > 1 - smoothTDiff) {
                // -> t=1
                adjustedTChange = std::max(minTChange, (std::sin(glm::pi<float>() * (1 - tArg) / (2.0f * smoothTDiff))) * tChange);
            }

            if (tBackwards) {
                tArg -= adjustedTChange;
                if (tArg <= 0) {
                    tArg = 0;
                    tBackwards = false;
                }
            } else {
                tArg += adjustedTChange;
                if (tArg >= 1) {
                    tArg = 1;
                    tBackwards = true;
                }
            }
            break;
    }

}

void BezierAnimation::DoAnimation(float t) {
    if (!Enabled) return;

    int numPoints = static_cast<int>(Points.size());
    if (numPoints < 4) {
        return;
    }

    int numSegments = (numPoints - 1) / 3;

    //map TArg to the number of segments
    //ensure that the segment index stays within the bounds of the available segments
    //max value is numSegments - 1
    int currentSegment = std::min(static_cast<int>(this->tArg * static_cast<float>(numSegments)), numSegments - 1);

    float localT = (tArg * static_cast<float>(numSegments)) - static_cast<float>(currentSegment);

    //current segment is complete?
    int startIndex = currentSegment * 3;
    if (startIndex + 3 < numPoints) {
        glm::vec3 p0 = Points.at(startIndex);
        glm::vec3 p1 = Points.at(startIndex + 1);
        glm::vec3 p2 = Points.at(startIndex + 2);
        glm::vec3 p3 = Points.at(startIndex + 3);

        Result = CalculateBezierCubic(localT, p0, p1, p2, p3);
    }

    NextStep();
}

void BezierAnimation::AddPoint(glm::vec3 point) {
    Points.push_back(point);
}

void BezierAnimation::ClearPoints() {
    Points.clear();
}

void BezierAnimation::SetStyle(BezierAnimation::BezierAnimationStyle newStyle) {
    this->Style = newStyle;
    this->tArg = 0;
}

void BezierAnimation::SetSmoothTDiff(float newSmoothTDiff) {

    if (newSmoothTDiff < 0.0f) {
        std::cerr << "BezierAnimation::SetSmoothTDiff: newSmoothTDiff < 0.0f" << std::endl;
        return;
    }

    if (newSmoothTDiff > 1.0f) {
        std::cerr << "BezierAnimation::SetSmoothTDiff: newSmoothTDiff > 1.0f" << std::endl;
        return;
    }

    this->smoothTDiff = newSmoothTDiff;
}

std::shared_ptr<Transformation> BezierAnimation::GetResult() const {
    return std::make_shared<Move>(Result);
}

int BezierAnimation::GetPointsCount() {
    return static_cast<int>(Points.size());
}


