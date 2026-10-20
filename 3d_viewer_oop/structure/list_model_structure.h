#pragma once

#include <vector>

#include "base_model_structure.h"

class ListModelStructure : public BaseModelStructure
{
public:
    ListModelStructure() = default;
    ~ListModelStructure() override = default;

    void add_point(const Point& point) override;
    void add_edge(const Edge& edge) override;

    std::vector<Point> get_points() const override;
    std::vector<Edge> get_edges() const override;

    Point get_center() const override;
    void set_center(const Point& new_center) override;

    void transform(const TransformParams& params) override;
    std::shared_ptr<BaseModelStructure> clone() const override;

private:
    std::vector<Point> points;
    std::vector<Edge> edges;
};