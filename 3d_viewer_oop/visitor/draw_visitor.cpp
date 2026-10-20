#include "draw_visitor.h"

#include "carcass_model_impl.h"
#include "base_model_structure.h"
#include "raycasting_hidden_edges_removal.h"

DrawVisitor::DrawVisitor(std::shared_ptr<BaseDrawer> d, std::shared_ptr<ObjectImpl> vi, int w, int h, bool show_invisible) : drawer(std::move(d)), viewer_impl(std::move(vi)), width(w), height(h), show_invisible_edges(show_invisible) {}

void DrawVisitor::visit(ObjectImpl& impl)
{
    auto* carcass = dynamic_cast<CarcassModelImpl*>(&impl);
    if (!carcass) 
        return;

    auto structure = carcass->get_structure();
    if (!structure) 
        return;

    auto points = structure->get_points();
    auto edges = structure->get_edges();
    Point center = structure->get_center();
    Point origin = Scene::get_instance().get_center();

    std::vector<Point> abs_points;
    for (auto& p : points)
        abs_points.push_back(Point(p.get_x() + center.get_x() + origin.get_x(), p.get_y() + center.get_y() + origin.get_y(), p.get_z() + center.get_z() + origin.get_z()));

    if (!show_invisible_edges)
    {
        RaycastingHiddenEdgesRemovalStrategy strategy;
        std::vector<std::pair<Point, Point>> visible_edges;
        strategy.prepare(abs_points, edges, viewer_impl, visible_edges);

        for (auto& [p1, p2] : visible_edges)
        {
            auto point_1 = project(p1);
            auto point_2 = project(p2);
            if (point_1.get_z() > 0 && point_2.get_z() > 0)
                drawer->draw_line(point_1, point_2);
        }
    }
    else
    {
        for (const auto& edge : edges)
        {
            auto point_1 = project(abs_points[edge.get_start()]);
            auto point_2 = project(abs_points[edge.get_end()]);
            if (point_1.get_z() > 0 && point_2.get_z() > 0)
                drawer->draw_line(point_1, point_2);
        }
    }
}

Point DrawVisitor::project(const Point& point) const
{
    Point cam = viewer_impl->get_position();
    Point dir = viewer_impl->get_direction();
    Point up = viewer_impl->get_up();
    Point right = viewer_impl->get_right();

    double dx = point.get_x() - cam.get_x();
    double dy = point.get_y() - cam.get_y();
    double dz = point.get_z() - cam.get_z();

    double proj_x = dx * right.get_x() + dy * right.get_y() + dz * right.get_z();
    double proj_y = dx * up.get_x()    + dy * up.get_y()    + dz * up.get_z();
    double proj_z = dx * dir.get_x()   + dy * dir.get_y()   + dz * dir.get_z();

    const double focus = 500.0;
    if (proj_z > 0)
    {
        proj_x = proj_x * focus / proj_z + width / 2.0;
        proj_y = proj_y * focus / proj_z + height / 2.0;
    }

    return {proj_x, proj_y, proj_z};
}