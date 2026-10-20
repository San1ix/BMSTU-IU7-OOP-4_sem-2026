#include "scene_manager.h"

#include "scene_memento.h"
#include "composite.h"

SceneManager::SceneManager() : scene(Scene::get_instance()) {}

std::shared_ptr<SceneManager> SceneManager::get_instance()
{
    static auto instance = std::shared_ptr<SceneManager>(new SceneManager);
    return instance;
}

Scene& SceneManager::get_scene() 
{ 
    return scene; 
}


Scene::iterator SceneManager::add_object(std::shared_ptr<BaseObj> obj)
{
    scene.add_object(obj);
    return --scene.end();
}

bool SceneManager::remove_object(std::size_t id)
{
    auto it = scene.get_object(id);
    if (it != scene.end()) 
        return scene.remove_object(it);
    return false;
}

Scene::iterator SceneManager::get_object(std::size_t id) 
{ 
    return scene.get_object(id); 
}

Scene::const_iterator SceneManager::get_object(std::size_t id) const 
{ 
    return scene.get_object(id); 
}

std::vector<std::size_t> SceneManager::get_object_ids() const
{
    std::vector<std::size_t> ids;
    for (auto it = scene.cbegin(); it != scene.cend(); it++)
        ids.push_back((*it)->get_id());
    return ids;
}

void SceneManager::clear_scene() 
{ 
    scene.clear(); 
}

void SceneManager::make_composite(const std::vector<std::size_t>& ids)
{
    auto composite = std::make_shared<Composite>();
    for (auto id : ids)
    {
        auto it = scene.get_object(id);
        if (it != scene.end())
        {
            composite->add(*it);
            scene.remove_object(it);
        }
    }
    scene.add_object(composite);
}

void SceneManager::decompose_composite(std::size_t id)
{
    auto it = scene.get_object(id);
    if (it == scene.end() || !(*it)->is_composite()) 
        return;

    auto composite = std::dynamic_pointer_cast<Composite>(*it);

    for (auto child = composite->begin(); child != composite->end(); child++)
        scene.add_object(*child);

    scene.remove_object(it);
}

void SceneManager::set_center(double x, double y, double z) 
{ 
    scene.set_center(x, y, z); 
}

std::shared_ptr<BaseMemento> SceneManager::create_memento()
{
    std::vector<std::shared_ptr<BaseObj>> objects;
    for (auto it = scene.begin(); it != scene.end(); it++)
        objects.push_back(*it);
    return std::make_shared<SceneMemento>(objects);
}

void SceneManager::restore_memento(std::shared_ptr<BaseMemento> memento)
{
    if (!memento) 
        return;
    scene.clear();
    for (auto& obj : memento->get_state())
        scene.add_object(obj);
}