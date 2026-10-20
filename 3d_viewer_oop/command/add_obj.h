#pragma once

#include "obj_cmd.h"
#include "base_obj.h"

class AddObj : public ObjCmd
{
public:
    explicit AddObj(std::shared_ptr<BaseObj> obj) : obj(obj) {}

    void execute(const Managers& managers) override 
    { 
        managers.scene_manager->add_object(obj); 
    }
    
private:
    std::shared_ptr<BaseObj> obj;
};