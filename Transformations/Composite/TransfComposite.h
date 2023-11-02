//
// Created by KOP0269 on 10/8/23.
//

#ifndef ZPG_TEST_TRANSFCOMPOSITE_H
#define ZPG_TEST_TRANSFCOMPOSITE_H


#include <vector>
#include <memory>
#include "Abstract/Transformation.h"

class TransfComposite : public Transformation {
private:
    std::vector<std::shared_ptr<Transformation>> Transformations;
    glm::mat4 Result = glm::mat4(1.0f);

public:
    void Insert(const std::shared_ptr<Transformation> &transformation);
    void ClearTransformations();
    glm::mat4 Use(const glm::mat4 &input) override;
    glm::mat4 Use();

    glm::mat4 UseAndRemember(const glm::mat4 &input);
    glm::mat4 UseAndRemember();

    glm::mat4 Consolidate(const glm::mat4 &input);
    glm::mat4 Consolidate();

    void SetResult(glm::mat4 result);
    [[nodiscard]] glm::mat4 GetResult() const;

    void ResetResult();
};

#endif //ZPG_TEST_TRANSFCOMPOSITE_H
