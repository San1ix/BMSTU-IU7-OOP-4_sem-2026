#pragma once

#include <vector>
#include <memory>
#include <cmath>

#include "point.h"
#include "edge.h"
#include "transform_params.h"

class BaseModelStructure
{
public:
    BaseModelStructure() = default;
    virtual ~BaseModelStructure() = default;

    virtual void add_point(const Point& point) = 0;
    virtual void add_edge(const Edge& edge) = 0;

    virtual std::vector<Point> get_points() const = 0;
    virtual std::vector<Edge> get_edges() const = 0;

    virtual Point get_center() const = 0;
    virtual void set_center(const Point& center) = 0;

    virtual void transform(const TransformParams& params) = 0;
    virtual std::shared_ptr<BaseModelStructure> clone() const = 0;

protected:
    Point center;

    void move(double dx, double dy, double dz);
    void rotate(std::vector<Point>& pts, double x_angle, double y_angle, double z_angle);
    void scale(std::vector<Point>& pts, double kx, double ky, double kz);
};