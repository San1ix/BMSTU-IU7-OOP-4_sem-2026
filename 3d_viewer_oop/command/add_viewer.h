#pragma once

#include "viewer_cmd.h"
#include "point.h"

class AddViewer : public ViewerCmd
{
public:
    explicit AddViewer(const Point& pos) : pos(pos) {}

    void execute(const Managers& managers) override 
    { 
        managers.viewer_manager->add_viewer(pos); 
    }
    
private:
    Point pos;
};