#pragma once

#include <memory>

#include "point.h"
#include "transform_params.h"

class BaseViewerImpl
{
public:
    BaseViewerImpl() = default;
    virtual ~BaseViewerImpl() = default;

    virtual Point get_position() const = 0;
    virtual Point get_direction() const = 0;
    virtual Point get_up() const = 0;
    virtual Point get_right() const = 0;

    virtual void look_at(const Point& target) = 0;
    virtual void transform(const TransformParams& params) = 0;

    virtual std::shared_ptr<BaseViewerImpl> clone() const = 0;
};