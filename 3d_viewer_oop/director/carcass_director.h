#pragma once

#include "base_director.h"
#include "base_builder.h"

class CarcassDirector : public BaseDirector
{
public:
    CarcassDirector() = default;
    ~CarcassDirector() override = default;

    void set_builder(std::shared_ptr<BaseBuilder> builder);
    std::shared_ptr<BaseObj> create(std::shared_ptr<BaseReader> reader) override;

private:
    std::shared_ptr<BaseBuilder> builder;
};