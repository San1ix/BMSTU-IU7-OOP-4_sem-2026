#include "viewer.h"

Viewer::Viewer() : InvisibleObj(std::make_shared<ViewerImplV1>()) {}
Viewer::Viewer(double x, double y, double z) : InvisibleObj(std::make_shared<ViewerImplV1>(x, y, z)) {}
Viewer::Viewer(const Point& pos) : InvisibleObj(std::make_shared<ViewerImplV1>(pos)) {}
Viewer::Viewer(const Viewer& other) : InvisibleObj(other) {}

std::shared_ptr<BaseObj> Viewer::clone() const
{
    return std::make_shared<Viewer>(*this);
}