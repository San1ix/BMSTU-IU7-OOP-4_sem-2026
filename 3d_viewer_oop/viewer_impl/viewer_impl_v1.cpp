#include "viewer_impl_v1.h"

ViewerImplV1::ViewerImplV1(double x, double y, double z) : position(x, y, z) {}

ViewerImplV1::ViewerImplV1(const Point& pos) : position(pos) {}

ViewerImplV1::ViewerImplV1(const ViewerImplV1& other) : position(other.position), direction(other.direction), up(other.up), right(other.right) {}

Point ViewerImplV1::get_position() const
{
    return position;
}

Point ViewerImplV1::get_direction() const
{
    return direction;
}

Point ViewerImplV1::get_up() const
{
    return up;
}

Point ViewerImplV1::get_right() const
{
    return right;
}

void ViewerImplV1::look_at(const Point& target)
{
    double dir_x = target.get_x() - position.get_x();
    double dir_y = target.get_y() - position.get_y();
    double dir_z = target.get_z() - position.get_z();
    direction.set(dir_x, dir_y, dir_z);

    double len = std::sqrt(dir_x * dir_x + dir_y * dir_y + dir_z * dir_z);

    if (len > 0)
        direction.set(dir_x / len, dir_y / len, dir_z / len);

    up.set(0, 1, 0);
    right.set(direction.get_z(), 0, -direction.get_x());
}

void ViewerImplV1::transform(const TransformParams& params)
{
    switch (params.type)
    {
        case TransformType::Move:
            move(params.x_param, params.y_param, params.z_param);
            break;
        case TransformType::Rotate:
            rotate(params.x_param, params.y_param, params.z_param);
            break;
        case TransformType::Scale:
            break;
    }
}

void ViewerImplV1::move(double dx, double dy, double dz)
{
    double x = position.get_x() + dx;
    double y = position.get_y() + dy;
    double z = position.get_z() + dz;
    position.set(x, y, z);
}

void ViewerImplV1::rotate_vector(Point& vec, double x_angle, double y_angle, double z_angle)
{
    double cos_x = std::cos(x_angle);
    double sin_x = std::sin(x_angle);

    double cos_y = std::cos(y_angle);
    double sin_y = std::sin(y_angle);

    double cos_z = std::cos(z_angle);
    double sin_z = std::sin(z_angle);

    double x = vec.get_x();
    double y = vec.get_y();
    double z = vec.get_z();

    double y1 = y * cos_x - z * sin_x;
    double z1 = y * sin_x + z * cos_x;
    double x1 = x * cos_y + z1 * sin_y;

    double x2 = x1 * cos_z - y1 * sin_z;
    double y2 = x1 * sin_z + y1 * cos_z;
    double z2 = -x * sin_y + z1 * cos_y;

    vec.set(x2, y2, z2);
}

void ViewerImplV1::rotate(double x_angle, double y_angle, double z_angle)
{
    rotate_vector(direction, x_angle, y_angle, z_angle);
    rotate_vector(up, x_angle, y_angle, z_angle);
    rotate_vector(right, x_angle, y_angle, z_angle);
}

std::shared_ptr<BaseViewerImpl> ViewerImplV1::clone() const
{
    return std::make_shared<ViewerImplV1>(*this);
}