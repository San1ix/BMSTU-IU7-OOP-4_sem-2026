#pragma once
#include "scene_cmd.h"

class SetCenter : public SceneCmd
{
public:
    SetCenter(double x, double y, double z) : x(x), y(y), z(z) {}

    void execute(const Managers& managers) override 
    { 
        managers.scene_manager->set_center(x, y, z); 
    }
    
private:
    double x, y, z;
};