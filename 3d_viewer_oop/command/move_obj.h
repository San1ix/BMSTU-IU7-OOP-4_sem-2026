#pragma once

#include "obj_cmd.h"
#include "transform_params.h"

class MoveObj : public ObjCmd
{
public:
    MoveObj(std::size_t id, double dx, double dy, double dz) : id(id), dx(dx), dy(dy), dz(dz) {}
    void execute(const Managers& managers) override 
    { 
        managers.transform_manager->transform_object(id, {TransformType::Move, dx, dy, dz}); 
    }
    
private:
    std::size_t id;
    double dx, dy, dz;
};