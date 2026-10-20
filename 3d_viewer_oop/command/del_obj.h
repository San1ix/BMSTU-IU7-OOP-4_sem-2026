#pragma once

#include "base_cmd.h"

class DelObj : public BaseCmd
{
public:
    explicit DelObj(std::size_t id) : id(id) {}
    
    void execute(const Managers& managers) override 
    { 
        managers.scene_manager->remove_object(id); 
    }

private:
    std::size_t id;
};