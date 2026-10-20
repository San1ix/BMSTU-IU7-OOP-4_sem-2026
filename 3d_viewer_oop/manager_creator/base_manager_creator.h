#pragma once

#include <memory>

#include "base_manager.h"

class BaseManagerCreator
{
public:
    BaseManagerCreator() = default;
    virtual ~BaseManagerCreator() = default;

    virtual std::shared_ptr<BaseManager> instance() = 0;
};