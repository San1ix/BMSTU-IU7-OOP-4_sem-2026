#pragma once

#include <vector>

#include "base_hidden_edges_removal.h"
#include "face_finder.h"
#include "ray_intersector.h"
#include "point_in_polygon_checker.h"

class RaycastingHiddenEdgesRemovalStrategy : public BaseHiddenEdgesRemovalStrategy
{
public:
    RaycastingHiddenEdgesRemovalStrategy() = default;
    ~RaycastingHiddenEdgesRemovalStrategy() override = default;

    void prepare(const std::vector<Point>& points, const std::vector<Edge>& edges, std::shared_ptr<const ObjectImpl> viewer, std::vector<Edge2D>& visible_edges) override;

private:
    FaceFinder face_finder;
    RayIntersector ray_intersector;
    PointInPolygonChecker point_checker;
};