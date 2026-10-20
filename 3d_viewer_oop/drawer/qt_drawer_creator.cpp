#include "qt_drawer_creator.h"

#include "qt_drawer.h"

std::shared_ptr<BaseDrawer> QtDrawerCreator::create(QGraphicsScene* scene)
{
    return std::make_shared<QtDrawer>(scene);
}