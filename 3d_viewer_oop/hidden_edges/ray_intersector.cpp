#include "ray_intersector.h"

#include <cmath>

std::optional<Point> RayIntersector::intersect_line_plane(const Point& p1, const Point& p2, const Plane& plane, double& t)
{
    double dx = p1.get_x() - p2.get_x();
    double dy = p1.get_y() - p2.get_y();
    double dz = p1.get_z() - p2.get_z();
    double dot = plane.a * dx + plane.b * dy + plane.c * dz;
    if (std::abs(dot) < 1e-9) 
        return std::nullopt;
    double val = plane.a * p1.get_x() + plane.b * p1.get_y() + plane.c * p1.get_z() + plane.d;
    t = -val / dot;
    return Point(p1.get_x() + t * dx, p1.get_y() + t * dy, p1.get_z() + t * dz);
}