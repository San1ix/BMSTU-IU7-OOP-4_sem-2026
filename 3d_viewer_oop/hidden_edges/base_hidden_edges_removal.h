#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "point.h"
#include "edge.h"
#include "object_impl.h"

class BaseHiddenEdgesRemovalStrategy
{
public:
    using Edge2D = std::pair<Point, Point>;

    BaseHiddenEdgesRemovalStrategy() = default;
    virtual ~BaseHiddenEdgesRemovalStrategy() = default;

    virtual void prepare(const std::vector<Point>& points, const std::vector<Edge>& edges, std::shared_ptr<const ObjectImpl> viewer, std::vector<Edge2D>& visible_edges) = 0;
};