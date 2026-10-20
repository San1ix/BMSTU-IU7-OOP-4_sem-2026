#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "base_director_creator.h"

class DirectorSolution
{
public:
    DirectorSolution();
    ~DirectorSolution() = default;

    std::shared_ptr<BaseDirectorCreator> create_creator(const std::string& type);

private:
    using CreatorFunc = std::function<std::shared_ptr<BaseDirectorCreator>()>;
    std::map<std::string, CreatorFunc> map;
};