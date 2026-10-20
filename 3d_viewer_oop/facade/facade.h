#pragma once

#include <QGraphicsScene>
#include <memory>

#include "base_cmd.h"
#include "managers.h"
#include "qt_drawer_creator.h"

class Facade
{
public:
    using SceneType = QGraphicsScene*;
    using DrawerCreator = QtDrawerCreator;

    Facade();
    ~Facade() = default;

    void execute(BaseCmd& command);

private:
    Managers managers;
};