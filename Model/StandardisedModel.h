//
// Created by KOP0269 on 10/6/23.
//

#ifndef ZPG_TEST_STANDARDISEDMODEL_H
#define ZPG_TEST_STANDARDISEDMODEL_H

#include <string>
#include "Abstract/BaseModelData.h"
#include "Material.h"
#include "../Transformations/Composite/TransfComposite.h"
#include "../Shaders/ShaderProgram/ShaderHandler.h"
#include "Abstract/RenderableObject.h"

class StandardisedModel : public BaseModelData, public RenderableObject {
private:
    std::shared_ptr<TransfComposite> Transformations;
    std::weak_ptr<ShaderHandler> SelectedShaderProgram;
    Material material;

public:
    StandardisedModel(const float *modelData, int modelDataSize, std::string stamp, std::string name = "None");
    ~StandardisedModel() override;
    StandardisedModel(const StandardisedModel &other) = delete;
    StandardisedModel &operator=(const StandardisedModel &other) = delete;
    StandardisedModel(StandardisedModel &&other) noexcept;
    StandardisedModel &operator=(StandardisedModel &&other) noexcept;

    [[nodiscard]] std::string Info() const override;
    [[nodiscard]] std::string Name() const;
    [[nodiscard]] std::string Stamp() const;

    StandardisedModel &InsertTransfMove(glm::vec3 transformation);
    StandardisedModel &InsertTransfRotate(float angle, glm::vec3 transformation);
    StandardisedModel &InsertTransfScale(glm::vec3 transformation);
    StandardisedModel &InsertTransfComposite(const std::shared_ptr<Transformation> &transformation);

    void ConsolidateTransf(glm::mat4 transformation = glm::mat4(1.0f)) const;
    void DoTransf(glm::mat4 transformation = glm::mat4(1.0f)) const;
    [[nodiscard]] glm::mat4 GetTransf() const override;
    void ClearTransf() const;
    void ResetTransf() const;
    void SetTransf(glm::mat4 transformation) const;

    void SetShaderProgram(std::shared_ptr<ShaderHandler> &shaderProgram);
    [[nodiscard]] const std::weak_ptr<ShaderHandler> &GetShaderProgram() const;

    void SetMaterial(Material newMaterial);
    [[nodiscard]] Material GetMaterial() const override;
};


#endif //ZPG_TEST_STANDARDISEDMODEL_H
