#include "transform_manager.h"

#include "transform_visitor.h"
#include "scene_manager.h"

std::shared_ptr<TransformManager> TransformManager::get_instance()
{
    static auto instance = std::shared_ptr<TransformManager>(new TransformManager);
    return instance;
}

void TransformManager::transform_object(std::size_t id, const TransformParams& params)
{
    auto sm = SceneManager::get_instance();
    auto it = sm->get_object(id);
    if (it != sm->get_scene().end())
    {
        TransformVisitor visitor(params);
        (*it)->accept(visitor);
    }
}