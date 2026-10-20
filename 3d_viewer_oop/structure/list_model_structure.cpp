#include "list_model_structure.h"

void ListModelStructure::add_point(const Point& point)
{
    points.push_back(point);
}

void ListModelStructure::add_edge(const Edge& edge)
{
    edges.push_back(edge);
}

std::vector<Point> ListModelStructure::get_points() const
{
    return points;
}

std::vector<Edge> ListModelStructure::get_edges() const
{
    return edges;
}

Point ListModelStructure::get_center() const
{
    return center;
}

void ListModelStructure::set_center(const Point& new_center)
{
    center = new_center;
}

void ListModelStructure::transform(const TransformParams& params)
{
    switch (params.type)
    {
        case TransformType::Move:
            move(params.x_param, params.y_param, params.z_param);
            break;
        case TransformType::Rotate:
            rotate(points, params.x_param, params.y_param, params.z_param);
            break;
        case TransformType::Scale:
            scale(points, params.x_param, params.y_param, params.z_param);
            break;
    }
}

std::shared_ptr<BaseModelStructure> ListModelStructure::clone() const
{
    auto copy = std::make_shared<ListModelStructure>();
    copy->center = center;
    copy->points = points;
    copy->edges = edges;
    return copy;
}