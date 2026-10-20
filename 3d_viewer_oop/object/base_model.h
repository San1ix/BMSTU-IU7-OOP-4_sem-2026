#pragma once

#include <memory>

#include "visible_obj.h"
#include "transform_params.h"
#include "base_model_structure.h"

class BaseModel : public VisibleObj
{
public:
    BaseModel() = default;
    virtual ~BaseModel() override = default;

    void accept(Visitor& visitor) override;
};