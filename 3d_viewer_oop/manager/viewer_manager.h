#pragma once

#include <memory>
#include <vector>

#include "base_manager.h"
#include "scene.h"
#include "viewer.h"
#include "point.h"

class ViewerManager : public BaseManager
{
public:
    static std::shared_ptr<ViewerManager> get_instance();
    ViewerManager(const ViewerManager&) = delete;
    ViewerManager& operator=(const ViewerManager&) = delete;

    std::shared_ptr<Viewer> add_viewer(const Point& pos);
    bool remove_viewer(std::size_t id);
    std::vector<std::size_t> get_viewer_ids() const;
    std::shared_ptr<Viewer> get_viewer(std::size_t id) const;
    void set_active_viewer(std::size_t id);
    std::shared_ptr<Viewer> get_active_viewer() const;

private:
    ViewerManager();
    Scene& scene;
    std::shared_ptr<Viewer> active_viewer;
};