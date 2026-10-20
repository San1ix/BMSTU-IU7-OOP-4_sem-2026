#pragma once

#include <vector>

#include "point.h"
#include "edge.h"
#include "face.h"

class FaceFinder
{
public:
    FaceFinder() = default;
    ~FaceFinder() = default;

    std::vector<Face> find_faces(const std::vector<Point>& points, const std::vector<Edge>& edges);
};