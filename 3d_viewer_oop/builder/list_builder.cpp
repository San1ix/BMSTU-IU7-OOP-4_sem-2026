#include "list_builder.h"

ListBuilder::ListBuilder() : structure(std::make_shared<ListModelStructure>()) {}

void ListBuilder::build_points(const std::vector<Point>& points)
{
    for (const auto& point : points)
        structure->add_point(point);
}


void ListBuilder::build_edges(const std::vector<Edge>& edges)
{
    for (const auto& edge : edges)
        structure->add_edge(edge);
}

void ListBuilder::build_center()
{
    auto points = structure->get_points();
    if (points.empty())
        return;

    double min_x = points[0].get_x();
    double min_y = points[0].get_y();
    double min_z = points[0].get_z();

    double max_x = points[0].get_x();
    double max_y = points[0].get_y();
    double max_z = points[0].get_z();
    
    for (const auto& point : points)
    {
        if (point.get_x() < min_x) 
            min_x = point.get_x();
        if (point.get_y() < min_y) 
            min_y = point.get_y();
        if (point.get_z() < min_z) 
            min_z = point.get_z();
        if (point.get_x() > max_x) 
            max_x = point.get_x();
        if (point.get_y() > max_y) 
            max_y = point.get_y();
        if (point.get_z() > max_z) 
            max_z = point.get_z();
    }

    double center_x = (min_x + max_x) / 2;
    double center_y = (min_y + max_y) / 2;
    double center_z = (min_z + max_z) / 2;
    structure->set_center({center_x, center_y, center_z});
}

std::shared_ptr<BaseModelStructure> ListBuilder::get_structure() const
{
    return structure;
}