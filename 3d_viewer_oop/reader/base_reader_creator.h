#pragma once

#include <memory>

#include "base_reader.h"

class BaseReaderCreator
{
public:
    BaseReaderCreator() = default;
    virtual ~BaseReaderCreator() = default;

    virtual std::shared_ptr<BaseReader> create(const char* filename) = 0;
};