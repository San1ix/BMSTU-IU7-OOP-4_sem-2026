#pragma once

#include "point.h"

class BaseDrawer
{
public:
    BaseDrawer() = default;
    virtual ~BaseDrawer() = default;

    virtual void draw_line(const Point& point1, const Point& point2) = 0;
    virtual void clear() = 0;
};