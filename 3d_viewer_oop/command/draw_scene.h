#pragma once
#include "scene_cmd.h"

class DrawScene : public SceneCmd
{
public:
    explicit DrawScene(bool show_invisible) : show_invisible(show_invisible) {}

    void execute(const Managers& managers) override 
    { 
        managers.draw_manager->draw_scene(show_invisible); 
    }
    
private:
    bool show_invisible;
};