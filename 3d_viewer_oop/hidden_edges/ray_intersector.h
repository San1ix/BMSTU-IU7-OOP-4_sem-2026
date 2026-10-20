#pragma once

#include <optional>

#include "point.h"
#include "plane.h"

class RayIntersector
{
public:
    RayIntersector() = default;
    ~RayIntersector() = default;

    std::optional<Point> intersect_line_plane(const Point& p1, const Point& p2, const Plane& plane, double& t);
};