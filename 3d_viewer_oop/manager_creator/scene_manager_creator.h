#pragma once

#include "base_manager_creator.h"
#include "scene_manager.h"

class SceneManagerCreator : public BaseManagerCreator
{
public:
    SceneManagerCreator() = default;
    ~SceneManagerCreator() override = default;

    std::shared_ptr<BaseManager> instance() override;
};