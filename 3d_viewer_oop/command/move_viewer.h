#pragma once

#include "viewer_cmd.h"
#include "transform_params.h"

class MoveViewer : public ViewerCmd
{
public:
    MoveViewer(std::size_t id, double dx, double dy, double dz) : id(id), dx(dx), dy(dy), dz(dz) {}
    
    void execute(const Managers& managers) override 
    { 
        managers.transform_manager->transform_object(id, {TransformType::Move, dx, dy, dz}); 
    }
    
private:
    std::size_t id;
    double dx, dy, dz;
};