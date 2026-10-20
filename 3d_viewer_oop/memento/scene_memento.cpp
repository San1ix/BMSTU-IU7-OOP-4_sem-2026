#include "scene_memento.h"

SceneMemento::SceneMemento(const std::vector<std::shared_ptr<BaseObj>>& objects)
{
    for (const auto& obj : objects)
        state.push_back(obj->clone());
}

const std::vector<std::shared_ptr<BaseObj>>& SceneMemento::get_state() const
{
    return state;
}