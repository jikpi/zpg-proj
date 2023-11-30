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
    Transformation* AdditiveTransformation; //Used for animations

    glm::mat4 Result = glm::mat4(1.0f);

    glm::mat4 MasterUseAndRemember(const glm::mat4 &input, bool isIdentity);

    glm::mat4 ReturnWithAdditiveTransformation(const glm::mat4 &input);
public:
    void Insert(const std::shared_ptr<Transformation> &transformation);
    void SingleUse(const std::shared_ptr<Transformation> &transformation);

    void ClearTransformations();
    glm::mat4 Use(const glm::mat4 &input) override;
    glm::mat4 Use();

    glm::mat4 UseAndRemember(const glm::mat4 &input);
    glm::mat4 UseAndRemember();

    [[nodiscard]] bool TransformationsEmpty() const;

    glm::mat4 Consolidate(const glm::mat4 &input);
    glm::mat4 Consolidate();

    void SetResult(glm::mat4 result);
    [[nodiscard]] glm::mat4 GetResult();

    void ResetResult();

    void SetAdditiveTransformation(const std::shared_ptr<Transformation> &additiveTransformation);
    void ClearAdditiveTransformation();
    [[nodiscard]] Transformation * GetAdditiveTransformation() const;
};

#endif //ZPG_TEST_TRANSFCOMPOSITE_H
