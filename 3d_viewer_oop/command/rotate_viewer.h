#pragma once

#include "viewer_cmd.h"
#include "transform_params.h"

class RotateViewer : public ViewerCmd
{
public:
    RotateViewer(std::size_t id, double ox, double oy, double oz) : id(id), ox(ox), oy(oy), oz(oz) {}
    
    void execute(const Managers& managers) override 
    { 
        managers.transform_manager->transform_object(id, {TransformType::Rotate, ox, oy, oz}); 
    }

private:
    std::size_t id;
    double ox, oy, oz;
};