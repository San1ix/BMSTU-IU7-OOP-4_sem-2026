#pragma once

#include <memory>

#include "point.h"
#include "transform_params.h"

class Visitor;

class ObjectImpl
{
public:
    ObjectImpl() = default;
    virtual ~ObjectImpl() = default;

    virtual void accept(Visitor& visitor) = 0;
    virtual void transform(const TransformParams& params) = 0;
    virtual Point get_center() const = 0;
    virtual std::shared_ptr<ObjectImpl> clone() const = 0;

    virtual Point get_position() const 
    { 
        return {0, 0, 0}; 
    }

    virtual Point get_direction() const 
    { 
        return {0, 0, 1}; 
    }

    virtual Point get_up() const 
    { 
        return {0, 1, 0}; 
    }

    virtual Point get_right() const 
    { 
        return {1, 0, 0}; 
    }

    virtual void look_at(const Point&) {}
};