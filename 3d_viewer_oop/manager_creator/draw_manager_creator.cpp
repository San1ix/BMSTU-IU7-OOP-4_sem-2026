#include "draw_manager_creator.h"

std::shared_ptr<BaseManager> DrawManagerCreator::instance()
{
    return DrawManager::get_instance();
}