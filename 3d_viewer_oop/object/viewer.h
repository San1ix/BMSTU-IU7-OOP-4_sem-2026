#pragma once

#include "invisible_obj.h"
#include "viewer_impl_v1.h"

class Viewer : public InvisibleObj
{
public:
    Viewer();
    Viewer(double x, double y, double z);
    explicit Viewer(const Point& pos);
    Viewer(const Viewer& other);
    std::shared_ptr<BaseObj> clone() const override;
};