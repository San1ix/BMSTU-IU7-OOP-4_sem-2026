#pragma once

#include "scene_cmd.h"

class ClearScene : public SceneCmd
{
public:
    ClearScene() = default;
    
    void execute(const Managers& managers) override 
    { 
        managers.scene_manager->clear_scene(); 
    }
};