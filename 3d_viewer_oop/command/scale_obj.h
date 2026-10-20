#pragma once

#include "obj_cmd.h"
#include "transform_params.h"

class ScaleObj : public ObjCmd
{
public:
    ScaleObj(std::size_t id, double kx, double ky, double kz) : id(id), kx(kx), ky(ky), kz(kz) {}

    void execute(const Managers& managers) override 
    { 
        managers.transform_manager->transform_object(id, {TransformType::Scale, kx, ky, kz}); 
    }
    
private:
    std::size_t id;
    double kx, ky, kz;
};