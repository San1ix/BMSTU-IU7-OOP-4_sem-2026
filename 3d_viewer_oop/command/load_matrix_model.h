#pragma once

#include "load_cmd.h"

class LoadMatrixModelCmd : public LoadCmd
{
public:
    LoadMatrixModelCmd() = default;

    void execute(const Managers& managers) override 
    { 
        managers.load_manager->read_model("matrix"); 
    }
};