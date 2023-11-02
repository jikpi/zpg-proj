//
// Created by KOP0269 on 10/8/23.
//

#ifndef ZPG_TEST_TRANSFORMATIONFACTORY_H
#define ZPG_TEST_TRANSFORMATIONFACTORY_H


#include <memory>
#include "../TransfComposite.h"

class TransformationFactory {
public:
    static std::shared_ptr<TransfComposite> CreateOrbit(glm::vec3 delta, float angle, glm::vec3 rotation);


};


#endif //ZPG_TEST_TRANSFORMATIONFACTORY_H
