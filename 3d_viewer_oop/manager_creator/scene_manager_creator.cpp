#include "scene_manager_creator.h"

std::shared_ptr<BaseManager> SceneManagerCreator::instance()
{
    return SceneManager::get_instance();
}