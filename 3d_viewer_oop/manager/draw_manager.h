#pragma once

#include <memory>

#include "base_manager.h"
#include "base_drawer.h"
#include "base_drawer_creator.h"
#include "concept.h"

class DrawManager : public BaseManager
{
public:
    static std::shared_ptr<DrawManager> get_instance();

    DrawManager(const DrawManager&) = delete;
    DrawManager& operator=(const DrawManager&) = delete;

    template <typename DrawerCr, typename SceneT>
    void set_drawer(SceneT scene)
    requires DrawerCreatorType<DrawerCr, SceneT>
    {
        auto creator = std::make_shared<DrawerCr>();
        m_drawer = creator->create(scene);
    }

    void draw_scene(bool show_invisible = false);
    void clear();

private:
    DrawManager() = default;
    std::shared_ptr<BaseDrawer> m_drawer;
};