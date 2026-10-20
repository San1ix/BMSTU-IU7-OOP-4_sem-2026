#pragma once

#include "obj_cmd.h"

class DecomposeComposite : public ObjCmd
{
public:
    explicit DecomposeComposite(std::size_t id) : id(id) {}
    void execute(const Managers& managers) override 
    { 
        managers.scene_manager->decompose_composite(id); 
    }
    
private:
    std::size_t id;
};