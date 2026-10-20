#include "matrix_model_structure.h"

void MatrixModelStructure::init_adj_matrix(std::size_t n)
{
    adj_matrix.assign(n, std::vector<bool>(n, false));
}

void MatrixModelStructure::add_point(const Point& point)
{
    points.push_back(point);
}

void MatrixModelStructure::add_edge(const Edge& edge)
{
    std::size_t first = edge.get_start();
    std::size_t second = edge.get_end();

    if (first >= points.size() || second >= points.size())
        throw EdgeOutOfPointsException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__);

    adj_matrix[first][second] = true;
    adj_matrix[second][first] = true;
}

std::vector<Point> MatrixModelStructure::get_points() const
{
    return points;
}

std::vector<Edge> MatrixModelStructure::get_edges() const
{
    std::vector<Edge> edges;

    for (std::size_t i = 0; i < points.size(); i++)
        for (std::size_t j = i + 1; j < points.size(); j++)
            if (adj_matrix[i][j])
                edges.emplace_back(i, j);

    return edges;
}

Point MatrixModelStructure::get_center() const
{
    return center;
}

void MatrixModelStructure::set_center(const Point& new_center)
{
    center = new_center;
}

void MatrixModelStructure::transform(const TransformParams& params)
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

std::shared_ptr<BaseModelStructure> MatrixModelStructure::clone() const
{
    auto copy = std::make_shared<MatrixModelStructure>();
    copy->center = center;
    copy->points = points;
    copy->adj_matrix = adj_matrix;
    return copy;
}