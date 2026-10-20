#pragma once

#include <memory>

#include "base_obj.h"
#include "base_reader.h"

class BaseDirector
{
public:
    BaseDirector() = default;
    virtual ~BaseDirector() = default;

    virtual std::shared_ptr<BaseObj> create(std::shared_ptr<BaseReader> reader) = 0;
};