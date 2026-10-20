#include "point_in_polygon_checker.h"

bool PointInPolygonChecker::is_point_in_polygon(const Point& point, const Face& face)
{
    int crossings = 0;
    double px = point.get_x(), py = point.get_y();
    for (size_t i = 0, j = face.points.size() - 1; i < face.points.size(); j = i++)
    {
        double pi_x = face.points[i].get_x(), pi_y = face.points[i].get_y();
        double pj_x = face.points[j].get_x(), pj_y = face.points[j].get_y();
        if (((pi_y <= py && py < pj_y) || (pj_y <= py && py < pi_y)) && (px < (pj_x - pi_x) * (py - pi_y) / (pj_y - pi_y) + pi_x))
            crossings++;
    }
    return (crossings % 2) == 1;
}