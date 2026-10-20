#pragma once

#include "base_obj.h"

class VisibleObj : public BaseObj
{
public:
    VisibleObj() = default;
    explicit VisibleObj(std::shared_ptr<ObjectImpl> i) : BaseObj(i) {}
    VisibleObj(const VisibleObj& other) : BaseObj(other) {}
    bool is_visible() const override 
    { 
        return true; 
    }
};