#pragma once

#include <memory>

#include "managers.h"

class BaseCmd
{
public:
    BaseCmd() = default;
    virtual ~BaseCmd() = default;

    virtual void execute(const Managers& managers) = 0;
};