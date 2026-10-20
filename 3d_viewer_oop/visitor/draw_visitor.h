#pragma once

#include <memory>

#include "visitor.h"
#include "point.h"
#include "base_drawer.h"
#include "object_impl.h"

class DrawVisitor : public Visitor
{
public:
    DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<ObjectImpl> viewer_impl, int width, int height, bool show_invisible = false);
    ~DrawVisitor() override = default;

    void visit(ObjectImpl& impl) override;
    Point project(const Point& point) const;

private:
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<ObjectImpl> viewer_impl;
    int width, height;
    bool show_invisible_edges;
};