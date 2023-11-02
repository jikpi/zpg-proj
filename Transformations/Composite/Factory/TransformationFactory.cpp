//
// Created by KOP0269 on 10/8/23.
//

#include "TransformationFactory.h"
#include "../Transformations/Move.h"
#include "../Transformations/Rotate.h"

std::shared_ptr<TransfComposite> TransformationFactory::CreateOrbit(glm::vec3 delta, float angle, glm::vec3 rotation) {
    std::shared_ptr<TransfComposite> orbit = std::make_shared<TransfComposite>();

    orbit->Insert(std::make_shared<Move>(delta));
    orbit->Insert(std::make_shared<Rotate>(angle, rotation));
    orbit->Insert(std::make_shared<Move>(-delta));

    return orbit;
}
