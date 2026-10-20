#include "base_model_structure.h"

void BaseModelStructure::move(double dx, double dy, double dz)
{
    double x = center.get_x() + dx;
    double y = center.get_y() + dy;
    double z = center.get_z() + dz;
    center.set(x, y, z);
}

void BaseModelStructure::rotate(std::vector<Point>& pts, double x_angle, double y_angle, double z_angle)
{
    double cos_x = std::cos(x_angle);
    double sin_x = std::sin(x_angle);

    double cos_y = std::cos(y_angle);
    double sin_y = std::sin(y_angle);

    double cos_z = std::cos(z_angle);
    double sin_z = std::sin(z_angle);

    for (auto& point : pts)
    {
        double x = point.get_x();
        double y = point.get_y();
        double z = point.get_z();

        double y1 = y * cos_x - z * sin_x;
        double z1 = y * sin_x + z * cos_x;
        double x1 = x * cos_y + z1 * sin_y;

        double z2 = -x * sin_y + z1 * cos_y;
        double x2 = x1 * cos_z - y1 * sin_z;
        double y2 = x1 * sin_z + y1 * cos_z;

        point.set(x2, y2, z2);
    }
}

void BaseModelStructure::scale(std::vector<Point>& pts, double kx, double ky, double kz)
{
    for (auto& point : pts)
    {
        double x = point.get_x() * kx;
        double y = point.get_y() * ky;
        double z = point.get_z() * kz;
        point.set(x, y, z);
    }
}
