#include "scene.h"

Scene& Scene::get_instance() 
{ 
    static Scene instance; 
    return instance; 
}

bool Scene::add_object(std::shared_ptr<BaseObj> obj) 
{ 
    objects.push_back(obj); 
    return true; 
}

bool Scene::remove_object(const_iterator it) 
{ 
    objects.erase(it); 
    return true; 
}

Scene::iterator Scene::get_object(std::size_t id)
{
    for (auto it = begin(); it != end(); it++)
        if ((*it)->get_id() == id) 
            return it;
    return end();
}

Scene::const_iterator Scene::get_object(std::size_t id) const
{
    for (auto it = begin(); it != end(); it++)
        if ((*it)->get_id() == id) 
            return it;
    return end();
}

Scene::iterator Scene::begin() noexcept 
{ 
    return objects.begin(); 
}
Scene::iterator Scene::end() noexcept 
{ 
    return objects.end(); 
}
Scene::const_iterator Scene::begin() const noexcept 
{ 
    return objects.begin(); 
}
Scene::const_iterator Scene::end() const noexcept 
{ 
    return objects.end(); 
}
Scene::const_iterator Scene::cbegin() const noexcept 
{ 
    return objects.cbegin(); 
}
Scene::const_iterator Scene::cend() const noexcept 
{ 
    return objects.cend(); 
}
Scene::size_type Scene::size() const noexcept 
{ 
    return objects.size(); 
}
void Scene::clear() 
{ 
    objects.clear(); 
}
