#include "viewer_manager.h"

ViewerManager::ViewerManager() : scene(Scene::get_instance()) {}

std::shared_ptr<ViewerManager> ViewerManager::get_instance()
{
    static auto instance = std::shared_ptr<ViewerManager>(new ViewerManager);
    return instance;
}

std::shared_ptr<Viewer> ViewerManager::add_viewer(const Point& pos)
{
    auto viewer = std::make_shared<Viewer>(pos);
    scene.add_object(viewer);
    if (!active_viewer) 
        active_viewer = viewer;
    return viewer;
}

bool ViewerManager::remove_viewer(std::size_t id)
{
    if (get_viewer_ids().size() <= 1) 
        return false;
    auto it = scene.get_object(id);
    if (it != scene.end() && !(*it)->is_visible())
    {
        if (active_viewer && active_viewer->get_id() == id)
        {
            active_viewer = nullptr;
            for (auto vid : get_viewer_ids())
                if (vid != id) 
                { 
                    set_active_viewer(vid); 
                    break; 
                }
        }
        return scene.remove_object(it);
    }
    return false;
}

std::vector<std::size_t> ViewerManager::get_viewer_ids() const
{
    std::vector<std::size_t> ids;
    for (auto it = scene.cbegin(); it != scene.cend(); it++)
        if (!(*it)->is_visible()) 
            ids.push_back((*it)->get_id());
    return ids;
}

std::shared_ptr<Viewer> ViewerManager::get_viewer(std::size_t id) const
{
    auto it = scene.get_object(id);
    if (it != scene.end() && !(*it)->is_visible())
        return std::dynamic_pointer_cast<Viewer>(*it);
    return nullptr;
}

void ViewerManager::set_active_viewer(std::size_t id)
{
    auto viewer = get_viewer(id);
    if (viewer) 
        active_viewer = viewer;
}

std::shared_ptr<Viewer> ViewerManager::get_active_viewer() const 
{ 
    return active_viewer; 
}
