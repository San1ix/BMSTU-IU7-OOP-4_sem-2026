#pragma once

#include "base_manager_creator.h"
#include "draw_manager.h"

class DrawManagerCreator : public BaseManagerCreator
{
public:
    DrawManagerCreator() = default;
    ~DrawManagerCreator() override = default;

    std::shared_ptr<BaseManager> instance() override;
};