#include "draw_manager.h"

#include "scene_manager.h"
#include "viewer_manager.h"
#include "draw_visitor.h"

std::shared_ptr<DrawManager> DrawManager::get_instance()
{
    static auto instance = std::shared_ptr<DrawManager>(new DrawManager);
    return instance;
}

void DrawManager::draw_scene(bool show_invisible)
{
    if (!m_drawer) 
        return;

    auto sm = SceneManager::get_instance();
    auto vm = ViewerManager::get_instance();
    auto viewer = vm->get_active_viewer();
    if (!viewer) 
        return;

    m_drawer->clear();

    DrawVisitor visitor(m_drawer, viewer->get_impl(), 500, 500, show_invisible);
    auto& scene = sm->get_scene();
    for (auto it = scene.begin(); it != scene.end(); it++)
        (*it)->accept(visitor);
}

void DrawManager::clear() 
{ 
    m_drawer.reset(); 
}
