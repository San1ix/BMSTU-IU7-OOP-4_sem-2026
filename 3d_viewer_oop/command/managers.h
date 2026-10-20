#pragma once

#include <memory>

#include "scene_manager.h"
#include "viewer_manager.h"
#include "transform_manager.h"
#include "draw_manager.h"
#include "load_manager.h"

struct Managers
{
    std::shared_ptr<SceneManager> scene_manager;
    std::shared_ptr<ViewerManager> viewer_manager;
    std::shared_ptr<TransformManager> transform_manager;
    std::shared_ptr<DrawManager> draw_manager;
    std::shared_ptr<LoadManager> load_manager;
};