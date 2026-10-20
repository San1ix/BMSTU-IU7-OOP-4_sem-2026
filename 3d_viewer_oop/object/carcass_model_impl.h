#pragma once

#include <memory>

#include "object_impl.h"
#include "scene.h"
#include "base_model_structure.h"

class CarcassModelImpl : public ObjectImpl
{
public:
    explicit CarcassModelImpl(std::shared_ptr<BaseModelStructure> s);
    CarcassModelImpl(const CarcassModelImpl& other);
    ~CarcassModelImpl() override = default;

    void accept(Visitor& visitor) override;
    void transform(const TransformParams& params) override;
    Point get_center() const override;
    std::shared_ptr<ObjectImpl> clone() const override;
    std::shared_ptr<BaseModelStructure> get_structure() const;

private:
    std::shared_ptr<BaseModelStructure> structure;
};