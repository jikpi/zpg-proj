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
    ShaderHandler* SelectedShaderProgram;
    unsigned short ContextID;

public:
    explicit StandardisedModel(ModelStamp stamp, std::string name = "None");
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

    void SetShaderProgram(ShaderHandler *shaderProgram);
    [[nodiscard]] ShaderHandler * GetShaderProgram() const;

    void SetContextID(unsigned short contextID);
    [[nodiscard]] unsigned short GetContextID() const;
    bool DesiredContextID;

    //Quick implementation of multiple meshes
    std::vector<std::shared_ptr<StandardisedModel>> ChildObjects;
    void SetChildrenTransformations();
};


#endif //ZPG_TEST_STANDARDISEDMODEL_H
