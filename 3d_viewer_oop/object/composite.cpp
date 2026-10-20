#include "composite.h"
#include "visitor.h"

Composite::Composite(std::vector<std::shared_ptr<BaseObj>> objs) : objects(std::move(objs)) {}
Composite::Composite(const Composite& other) : BaseObj(other) {}

bool Composite::add(std::shared_ptr<BaseObj> obj) 
{ 
    objects.push_back(obj); 
    return true; 
}

bool Composite::remove(const iterator& it) 
{ 
    objects.erase(it); 
    return true; 
}

void Composite::accept(Visitor& visitor)
{
    for (auto& obj : objects) 
        obj->accept(visitor);
}

std::shared_ptr<BaseObj> Composite::clone() const
{
    auto copy = std::make_shared<Composite>(*this);
    copy->objects.clear();
    for (const auto& obj : objects)
        copy->add(obj->clone());
    return copy;
}

Point Composite::get_center() const
{
    Point origin = Scene::get_instance().get_center();
    if (objects.empty()) 
        return origin;
    double cx = 0, cy = 0, cz = 0;
    for (const auto& obj : objects) 
    {
        auto c = obj->get_center();
        cx += c.get_x(); cy += c.get_y(); cz += c.get_z();
    }
    return {cx / objects.size() + origin.get_x(), cy / objects.size() + origin.get_y(), cz / objects.size() + origin.get_z()};
}
BaseObj::iterator Composite::begin() noexcept 
{ 
    return objects.begin(); 
}

BaseObj::iterator Composite::end() noexcept 
{ 
    return objects.end(); 
}

std::vector<std::size_t> Composite::get_child_ids() const
{
    std::vector<std::size_t> ids;
    for (const auto& obj : objects) 
        ids.push_back(obj->get_id());
    return ids;
}