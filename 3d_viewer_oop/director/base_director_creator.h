#pragma once

#include <memory>
#include <string>

#include "base_director.h"

class BaseDirectorCreator
{
public:
    BaseDirectorCreator() = default;
    virtual ~BaseDirectorCreator() = default;

    virtual std::shared_ptr<BaseDirector> create(const std::string& type) = 0;
};