#pragma once

#include "base_drawer_creator.h"
#include <QGraphicsScene>

class QtDrawerCreator : public BaseDrawerCreator<QGraphicsScene*>
{
public:
    QtDrawerCreator() = default;
    ~QtDrawerCreator() override = default;
    std::shared_ptr<BaseDrawer> create(QGraphicsScene* scene) override;
};