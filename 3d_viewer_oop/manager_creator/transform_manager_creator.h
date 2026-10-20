#pragma once

#include "base_manager_creator.h"
#include "transform_manager.h"

class TransformManagerCreator : public BaseManagerCreator
{
public:
    TransformManagerCreator() = default;
    ~TransformManagerCreator() override = default;

    std::shared_ptr<BaseManager> instance() override;
};