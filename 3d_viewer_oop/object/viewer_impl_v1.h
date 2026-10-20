#pragma once

#include "object_impl.h"
#include "scene.h"
#include "visitor.h"

class ViewerImplV1 : public ObjectImpl
{
public:
    ViewerImplV1() = default;
    ViewerImplV1(double x, double y, double z);
    explicit ViewerImplV1(const Point& pos);
    ViewerImplV1(const ViewerImplV1& other);
    ~ViewerImplV1() override = default;

    void accept(Visitor& visitor) override 
    { 
        visitor.visit(*this); 
    }

    void transform(const TransformParams& params) override;
    Point get_center() const override;

    std::shared_ptr<ObjectImpl> clone() const override;

    Point get_position() const override 
    { 
        return position; 
    }

    Point get_direction() const override 
    { 
        return direction; 
    }

    Point get_up() const override 
    { 
        return up; 
    }

    Point get_right() const override 
    {
        return right; 
    }
    
    void look_at(const Point& target) override;

private:
    Point position;
    Point direction{0, 0, 1};
    Point up{0, 1, 0};
    Point right{1, 0, 0};

    void move(double dx, double dy, double dz);
    void rotate(double x_angle, double y_angle, double z_angle);
    void rotate_vector(Point& vec, double x_angle, double y_angle, double z_angle);
};