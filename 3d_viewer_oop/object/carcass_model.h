#pragma once

#include "visible_obj.h"
#include "carcass_model_impl.h"

class CarcassModel : public VisibleObj
{
public:
    explicit CarcassModel(std::shared_ptr<CarcassModelImpl> i);
    std::shared_ptr<BaseObj> clone() const override;
};