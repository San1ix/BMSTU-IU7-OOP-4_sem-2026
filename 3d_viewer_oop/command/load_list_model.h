#pragma once

#include "load_cmd.h"

class LoadListModelCmd : public LoadCmd
{
public:
    LoadListModelCmd() = default;

    void execute(const Managers& managers) override 
    { 
        managers.load_manager->read_model("list"); 
    }
};