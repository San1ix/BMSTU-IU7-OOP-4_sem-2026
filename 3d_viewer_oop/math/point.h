#pragma once

class Point
{
public:
    Point() = default;
    Point(double x, double y, double z);
    Point(const Point& other) = default;
    Point(Point&& other) noexcept = default;

    Point& operator=(const Point& other) = default;
    Point& operator=(Point&& other) noexcept = default;

    ~Point() = default;

    double get_x() const;
    double get_y() const;
    double get_z() const;

    void set_x(double val);
    void set_y(double val);
    void set_z(double val);

    void set(double x_val, double y_val, double z_val);
    void set(const Point& other);

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

private:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};