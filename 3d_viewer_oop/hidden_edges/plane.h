#pragma once

#include "point.h"

struct Plane
{
    double a = 0, b = 0, c = 0, d = 0;
    Plane() = default;
    Plane(const Point& p1, const Point& p2, const Point& p3);
};