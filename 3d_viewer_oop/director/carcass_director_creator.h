#pragma once

#include "base_director_creator.h"
#include "carcass_director.h"
#include "builder_solution.h"

class CarcassDirectorCreator : public BaseDirectorCreator
{
public:
    CarcassDirectorCreator() = default;
    ~CarcassDirectorCreator() override = default;

    std::shared_ptr<BaseDirector> create(const std::string& type) override;
};