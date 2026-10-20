#pragma once

#include <memory>
#include <vector>

#include "base_manager.h"
#include "scene.h"
#include "base_obj.h"
#include "base_memento.h"

class SceneManager : public BaseManager
{
public:
    static std::shared_ptr<SceneManager> get_instance();
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    Scene& get_scene();

    Scene::iterator add_object(std::shared_ptr<BaseObj> obj);
    bool remove_object(std::size_t id);
    Scene::iterator get_object(std::size_t id);
    Scene::const_iterator get_object(std::size_t id) const;
    std::vector<std::size_t> get_object_ids() const;

    void clear_scene();
    void make_composite(const std::vector<std::size_t>& ids);
    void decompose_composite(std::size_t id);
    void set_center(double x, double y, double z);

    std::shared_ptr<BaseMemento> create_memento();
    void restore_memento(std::shared_ptr<BaseMemento> memento);

private:
    SceneManager();
    Scene& scene;
};