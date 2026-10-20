#include "viewer_manager_creator.h"

std::shared_ptr<BaseManager> ViewerManagerCreator::instance()
{
    return ViewerManager::get_instance();
}