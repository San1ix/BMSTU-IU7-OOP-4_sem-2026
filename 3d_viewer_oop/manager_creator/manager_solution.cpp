#include "manager_solution.h"

std::shared_ptr<SceneManager> ManagerSolution::get_scene_manager()
{
    return std::static_pointer_cast<SceneManager>(SceneManagerCreator().instance());
}

std::shared_ptr<ViewerManager> ManagerSolution::get_viewer_manager()
{
    return std::static_pointer_cast<ViewerManager>(ViewerManagerCreator().instance());
}

std::shared_ptr<TransformManager> ManagerSolution::get_transform_manager()
{
    return std::static_pointer_cast<TransformManager>(TransformManagerCreator().instance());
}

std::shared_ptr<DrawManager> ManagerSolution::get_draw_manager()
{
    return std::static_pointer_cast<DrawManager>(DrawManagerCreator().instance());
}

std::shared_ptr<LoadManager> ManagerSolution::get_load_manager()
{
    return std::static_pointer_cast<LoadManager>(LoadManagerCreator().instance());
}