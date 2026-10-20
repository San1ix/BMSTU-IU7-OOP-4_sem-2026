#include "raycasting_hidden_edges_removal.h"

#include "plane.h"

void RaycastingHiddenEdgesRemovalStrategy::prepare(const std::vector<Point>& points, const std::vector<Edge>& edges, std::shared_ptr<const ObjectImpl> viewer, std::vector<Edge2D>& visible_edges)
{
    auto faces = face_finder.find_faces(points, edges);
    auto viewpoint = viewer->get_position();

    for (const auto& edge : edges)
    {
        auto start = points[edge.get_start()];
        auto end = points[edge.get_end()];
        bool start_visible = true, end_visible = true;

        for (const auto& face : faces)
        {
            bool start_in_face = false, end_in_face = false;
            for (const auto& fp : face.points)
            {
                if (fp == start) 
                    start_in_face = true;
                if (fp == end) 
                    end_in_face = true;
            }

            double t;
            if (!start_in_face)
            {
                auto intersection = ray_intersector.intersect_line_plane(viewpoint, start, Plane(face.points[0], face.points[1], face.points[2]), t);
                if (intersection && t < 0 && std::abs(t) > 1e-6 && std::abs(t) < 1.0)
                    if (point_checker.is_point_in_polygon(*intersection, face))
                        start_visible = false;
            }
            
            if (!end_in_face)
            {
                auto intersection = ray_intersector.intersect_line_plane(viewpoint, end, Plane(face.points[0], face.points[1], face.points[2]), t);
                if (intersection && t < 0 && std::abs(t) > 1e-6 && std::abs(t) < 1.0)
                    if (point_checker.is_point_in_polygon(*intersection, face))
                        end_visible = false;
            }
        }
        if (start_visible && end_visible)
            visible_edges.push_back({start, end});
    }
}