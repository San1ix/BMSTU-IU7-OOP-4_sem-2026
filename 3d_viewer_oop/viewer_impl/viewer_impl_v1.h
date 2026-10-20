#pragma once

#include <cmath>

#include "base_viewer_impl.h"

class ViewerImplV1 : public BaseViewerImpl
{
public:
    ViewerImplV1() = default;
    ViewerImplV1(double x, double y, double z);
    explicit ViewerImplV1(const Point& pos);
    ViewerImplV1(const ViewerImplV1& other);
    ~ViewerImplV1() override = default;

    Point get_position() const override;
    Point get_direction() const override;
    Point get_up() const override;
    Point get_right() const override;

    void look_at(const Point& target) override;
    void transform(const TransformParams& params) override;

    std::shared_ptr<BaseViewerImpl> clone() const override;

private:
    Point position;
    Point direction{0, 0, 1};
    Point up{0, 1, 0};
    Point right{1, 0, 0};

    void move(double dx, double dy, double dz);
    void rotate(double x_angle, double y_angle, double z_angle);
    void rotate_vector(Point& vec, double x_angle, double y_angle, double z_angle);
};
