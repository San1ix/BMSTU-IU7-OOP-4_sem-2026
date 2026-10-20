#include "base_obj.h"

#include "object_impl.h"
#include "visitor.h"

static std::size_t id_counter = 0;
static std::size_t next_id() 
{ 
    return ++id_counter; 
}

BaseObj::BaseObj() : id(next_id()) {}
BaseObj::BaseObj(std::shared_ptr<ObjectImpl> i) : id(next_id()), impl(i) {}
BaseObj::BaseObj(const BaseObj& other) : id(other.id) {}

std::size_t BaseObj::get_id() const 
{ 
    return id; 
}

void BaseObj::set_id(std::size_t new_id) 
{ 
    id = new_id; 
}

void BaseObj::reset_id_counter(std::size_t value) 
{ 
    id_counter = value; 
}

std::size_t BaseObj::get_id_counter() 
{ 
    return id_counter; 
}

void BaseObj::accept(Visitor& visitor) 
{ 
    if (impl) 
        impl->accept(visitor); }
Point BaseObj::get_center() const 
{ 
    return impl ? impl->get_center() : Point(); 
}