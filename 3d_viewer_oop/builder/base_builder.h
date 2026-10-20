#pragma once

#include <memory>
#include <vector>

#include "point.h"
#include "edge.h"
#include "base_model_structure.h"

class BaseBuilder
{
public:
    BaseBuilder() = default;
    virtual ~BaseBuilder() = default;

    virtual void build_points(const std::vector<Point>& points) = 0;
    virtual void build_edges(const std::vector<Edge>& edges) = 0;
    virtual void build_center() = 0;

    virtual std::shared_ptr<BaseModelStructure> get_structure() const = 0;
};