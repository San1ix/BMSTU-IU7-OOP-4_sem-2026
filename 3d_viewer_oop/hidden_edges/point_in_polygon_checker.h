#pragma once

#include "point.h"
#include "face.h"

class PointInPolygonChecker
{
public:
    PointInPolygonChecker() = default;
    ~PointInPolygonChecker() = default;

    bool is_point_in_polygon(const Point& point, const Face& face);
};