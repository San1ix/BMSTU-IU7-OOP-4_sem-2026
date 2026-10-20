#pragma once

#include <memory>
#include <vector>
#include <cstddef>

#include "point.h"

class Visitor;
class ObjectImpl;

class BaseObj
{
public:
    using iterator = std::vector<std::shared_ptr<BaseObj>>::iterator;
    using const_iterator = std::vector<std::shared_ptr<BaseObj>>::const_iterator;

    BaseObj();
    explicit BaseObj(std::shared_ptr<ObjectImpl> impl);
    BaseObj(const BaseObj& other);
    virtual ~BaseObj() = default;

    std::size_t get_id() const;
    void set_id(std::size_t new_id);
    static void reset_id_counter(std::size_t value);
    static std::size_t get_id_counter();

    virtual void accept(Visitor& visitor);
    virtual std::shared_ptr<BaseObj> clone() const = 0;

    virtual bool is_visible() const = 0;
    virtual bool is_composite() const 
    { 
        return false; 
    }

    virtual Point get_center() const;

    virtual bool add(std::shared_ptr<BaseObj>) 
    { 
        return false; 
    }

    virtual bool remove(const iterator&) 
    { 
        return false; 
    }

    virtual iterator begin() noexcept 
    { 
        return {}; 
    }

    virtual iterator end() noexcept 
    { 
        return {}; 
    }

    std::shared_ptr<ObjectImpl> get_impl() const 
    { 
        return impl; 
    }

protected:
    std::shared_ptr<ObjectImpl> impl;

private:
    std::size_t id;
};