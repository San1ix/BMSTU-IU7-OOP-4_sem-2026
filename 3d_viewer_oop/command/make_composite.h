#pragma once

#include "obj_cmd.h"

class MakeComposite : public ObjCmd
{
public:
    explicit MakeComposite(const std::vector<std::size_t>& ids) : ids(ids) {}

    void execute(const Managers& managers) override 
    { 
        managers.scene_manager->make_composite(ids); 
    }
    
private:
    std::vector<std::size_t> ids;
};