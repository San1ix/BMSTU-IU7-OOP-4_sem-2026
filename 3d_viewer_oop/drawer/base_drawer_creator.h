#pragma once

#include <memory>

#include "base_drawer.h"
#include "concept.h"

template <typename SceneT>
class BaseDrawerCreator
{
public:
    BaseDrawerCreator() = default;
    virtual ~BaseDrawerCreator() = default;
    virtual std::shared_ptr<BaseDrawer> create(SceneT scene) = 0;
};

template <typename DrawerCr, typename SceneT>
concept DrawerCreatorType = Derivative<DrawerCr, BaseDrawerCreator<SceneT>> && Constructible<DrawerCr>;