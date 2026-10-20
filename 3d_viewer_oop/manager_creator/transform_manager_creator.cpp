#include "transform_manager_creator.h"

std::shared_ptr<BaseManager> TransformManagerCreator::instance()
{
    return TransformManager::get_instance();
}