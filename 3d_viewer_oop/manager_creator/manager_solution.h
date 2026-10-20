#pragma once

#include <memory>

#include "scene_manager.h"
#include "viewer_manager.h"
#include "transform_manager.h"
#include "draw_manager.h"
#include "load_manager.h"
#include "scene_manager_creator.h"
#include "viewer_manager_creator.h"
#include "transform_manager_creator.h"
#include "draw_manager_creator.h"
#include "load_manager_creator.h"

class ManagerSolution
{
public:
    ManagerSolution() = delete;
    ~ManagerSolution() = delete;
    ManagerSolution(const ManagerSolution&) = delete;

    static std::shared_ptr<SceneManager> get_scene_manager();
    static std::shared_ptr<ViewerManager> get_viewer_manager();
    static std::shared_ptr<TransformManager> get_transform_manager();
    static std::shared_ptr<DrawManager> get_draw_manager();
    static std::shared_ptr<LoadManager> get_load_manager();
};