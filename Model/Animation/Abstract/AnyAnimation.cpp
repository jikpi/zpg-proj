//
// Created by lvi on 30.11.23.
//

#include <iostream>
#include "AnyAnimation.h"

void AnyAnimation::SetTChange(float new_tChange) {
    if (new_tChange < 0.0f) {
        std::cerr << "BezierAnimation::SetTChange: new_tChange < 0.0f" << std::endl;
        return;
    }

    this->tChange = new_tChange;
}

AnyAnimation::AnyAnimation(float tChange) {
    this->tChange = tChange;
}
