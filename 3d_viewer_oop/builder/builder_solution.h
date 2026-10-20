#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "base_builder.h"

class BuilderSolution
{
public:
    BuilderSolution();
    ~BuilderSolution() = default;

    std::shared_ptr<BaseBuilder> create_builder(const std::string& type);

private:
    using CreatorFunc = std::function<std::shared_ptr<BaseBuilder>()>;
    std::map<std::string, CreatorFunc> map;
};