#include "load_manager_creator.h"

std::shared_ptr<BaseManager> LoadManagerCreator::instance()
{
    return LoadManager::get_instance();
}