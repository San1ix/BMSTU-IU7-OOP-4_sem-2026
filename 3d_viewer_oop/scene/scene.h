#pragma once

#include <list>
#include <memory>

#include "base_obj.h"

class Scene
{
public:
    using iterator = std::list<std::shared_ptr<BaseObj>>::iterator;
    using const_iterator = std::list<std::shared_ptr<BaseObj>>::const_iterator;
    using size_type = std::list<std::shared_ptr<BaseObj>>::size_type;

    Scene() = default;
    static Scene& get_instance();
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    bool add_object(std::shared_ptr<BaseObj> obj);
    bool remove_object(const_iterator it);
    iterator get_object(std::size_t id);
    const_iterator get_object(std::size_t id) const;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    size_type size() const noexcept;
    void clear();

    void set_center(double x, double y, double z) 
    { 
        center = Point(x, y, z); 
    }

    Point get_center() const 
    { 
        return center; 
    }

private:
    std::list<std::shared_ptr<BaseObj>> objects;
    Point center{0, 0, 0};
};