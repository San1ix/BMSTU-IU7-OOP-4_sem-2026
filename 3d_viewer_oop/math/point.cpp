#include "point.h"

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

double Point::get_x() const
{
    return x;
}

double Point::get_y() const
{
    return y;
}

double Point::get_z() const
{
    return z;
}

void Point::set_x(double val)
{
    x = val;
}

void Point::set_y(double val)
{
    y = val;
}

void Point::set_z(double val)
{
    z = val;
}

void Point::set(double x_val, double y_val, double z_val)
{
    x = x_val;
    y = y_val;
    z = z_val;
}

void Point::set(const Point& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

bool Point::operator==(const Point& other) const
{
    return x == other.x && y == other.y && z == other.z;
}

bool Point::operator!=(const Point& other) const
{
    return !(*this == other);
}
