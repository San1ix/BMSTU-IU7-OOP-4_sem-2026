#include "qt_drawer.h"

#include <QPen>

QtDrawer::QtDrawer(QGraphicsScene* scene) : scene(scene) {}

void QtDrawer::draw_line(const Point& point1, const Point& point2)
{
    scene->addLine(point1.get_x(), point1.get_y(), point2.get_x(), point2.get_y(), QPen(QColor(255, 105, 180), 2));
}

void QtDrawer::clear()
{
    scene->clear();
}