#include "facade.h"

#include "scene_manager.h"
#include "viewer_manager.h"
#include "transform_manager.h"
#include "draw_manager.h"
#include "load_manager.h"

Facade::Facade()
{
    managers.draw_manager = DrawManager::get_instance();
    managers.load_manager = LoadManager::get_instance();
    managers.scene_manager = SceneManager::get_instance();
    managers.transform_manager = TransformManager::get_instance();
    managers.viewer_manager = ViewerManager::get_instance();
}

void Facade::execute(BaseCmd& command)
{
    command.execute(managers);
}