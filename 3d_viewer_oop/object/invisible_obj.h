#pragma once

#include "base_obj.h"

class InvisibleObj : public BaseObj
{
public:
    InvisibleObj() = default;
    explicit InvisibleObj(std::shared_ptr<ObjectImpl> i) : BaseObj(i) {}
    InvisibleObj(const InvisibleObj& other) : BaseObj(other) {}
    bool is_visible() const override 
    { 
        return false; 
    }
};