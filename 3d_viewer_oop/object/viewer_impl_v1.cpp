#include "viewer_impl_v1.h"

#include <cmath>

ViewerImplV1::ViewerImplV1(double x, double y, double z) : position(x, y, z) {}
ViewerImplV1::ViewerImplV1(const Point& pos) : position(pos) {}
ViewerImplV1::ViewerImplV1(const ViewerImplV1& other) : position(other.position), direction(other.direction), up(other.up), right(other.right) {}

Point ViewerImplV1::get_center() const
{
    Point origin = Scene::get_instance().get_center();
    return {position.get_x() + origin.get_x(), position.get_y() + origin.get_y(), position.get_z() + origin.get_z()};
}

void ViewerImplV1::look_at(const Point& target)
{
    double dir_x = target.get_x() - position.get_x();
    double dir_y = target.get_y() - position.get_y();
    double dir_z = target.get_z() - position.get_z();
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
    position.set(position.get_x() + dx, position.get_y() + dy, position.get_z() + dz);
}

void ViewerImplV1::rotate(double x_angle, double y_angle, double z_angle)
{
    rotate_vector(direction, x_angle, y_angle, z_angle);
    rotate_vector(up, x_angle, y_angle, z_angle);
    rotate_vector(right, x_angle, y_angle, z_angle);
}

void ViewerImplV1::rotate_vector(Point& vec, double x_angle, double y_angle, double z_angle)
{
    double cos_x = std::cos(x_angle), sin_x = std::sin(x_angle);
    double cos_y = std::cos(y_angle), sin_y = std::sin(y_angle);
    double cos_z = std::cos(z_angle), sin_z = std::sin(z_angle);

    double x = vec.get_x(), y = vec.get_y(), z = vec.get_z();

    double y1 = y * cos_x - z * sin_x;
    double z1 = y * sin_x + z * cos_x;
    double x1 = x * cos_y + z1 * sin_y;
    double z2 = -x * sin_y + z1 * cos_y;
    
    vec.set(x1 * cos_z - y1 * sin_z, x1 * sin_z + y1 * cos_z, z2);
}

std::shared_ptr<ObjectImpl> ViewerImplV1::clone() const 
{ 
    return std::make_shared<ViewerImplV1>(*this); 
}
