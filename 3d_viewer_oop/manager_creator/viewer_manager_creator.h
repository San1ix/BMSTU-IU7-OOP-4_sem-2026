#pragma once

#include "base_manager_creator.h"
#include "viewer_manager.h"

class ViewerManagerCreator : public BaseManagerCreator
{
public:
    ViewerManagerCreator() = default;
    ~ViewerManagerCreator() override = default;

    std::shared_ptr<BaseManager> instance() override;
};