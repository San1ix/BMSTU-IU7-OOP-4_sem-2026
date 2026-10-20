#pragma once

#include "base_manager_creator.h"
#include "load_manager.h"

class LoadManagerCreator : public BaseManagerCreator
{
public:
    LoadManagerCreator() = default;
    ~LoadManagerCreator() override = default;

    std::shared_ptr<BaseManager> instance() override;
};