//
// Created by KOP0269 on 10/27/23.
//

#ifndef ZPG_TEST_RENDERABLEOBJECT_H
#define ZPG_TEST_RENDERABLEOBJECT_H


#include <memory>
#include "glm/ext/matrix_float4x4.hpp"
#include "../Material.h"
#include "../../Transformations/Composite/TransfComposite.h"

class RenderableObject {
protected:
    std::shared_ptr<TransfComposite> Transformations;
    Material material;

    glm::mat3 NormalMatrix;
    bool HasBeenTransformed;
public:
    virtual ~RenderableObject() = default;
    [[nodiscard]] virtual glm::mat4 GetTransf() const;
    void ConsolidateTransf(glm::mat4 transformation = glm::mat4(1.0f));
    void DoTransf(glm::mat4 transformation);
    void DoTransf();
    void ClearTransf();
    void ResetTransf();
    void SetTransf(glm::mat4 transformation);

    void SetMaterial(Material newMaterial);
    [[nodiscard]] Material GetMaterial() const;

    void SetTexture(Texture *texture);
    Texture *GetTexture();

    glm::mat3 &GetNormalMatrix();
};


#endif //ZPG_TEST_RENDERABLEOBJECT_H
