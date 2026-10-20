#include "plane.h"

#include <cmath>

Plane::Plane(const Point& p1, const Point& p2, const Point& p3)
{
    double ax = p2.get_x() - p1.get_x();
    double ay = p2.get_y() - p1.get_y();
    double az = p2.get_z() - p1.get_z();

    double bx = p3.get_x() - p1.get_x();
    double by = p3.get_y() - p1.get_y();
    double bz = p3.get_z() - p1.get_z();

    a = ay * bz - az * by;
    b = az * bx - ax * bz;
    c = ax * by - ay * bx;

    double len = std::sqrt(a * a + b * b + c * c);
    if (len > 0) 
    { 
        a /= len;
        b /= len;
        c /= len; 
    }

    d = -(a * p1.get_x() + b * p1.get_y() + c * p1.get_z());
}