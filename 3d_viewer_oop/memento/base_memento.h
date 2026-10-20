#pragma once

#include <vector>
#include <memory>

#include "base_obj.h"

class BaseMemento
{
public:
    BaseMemento() = default;
    virtual ~BaseMemento() = default;

    virtual const std::vector<std::shared_ptr<BaseObj>>& get_state() const = 0;
};