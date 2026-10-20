#pragma once

#include <QGraphicsScene>

#include "base_drawer.h"

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = default;
    explicit QtDrawer(QGraphicsScene* scene);
    ~QtDrawer() override = default;

    void draw_line(const Point& point1, const Point& point2) override;
    void clear() override;

private:
    QGraphicsScene* scene;
};