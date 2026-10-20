#pragma once

#include "viewer_cmd.h"

class SetViewer : public ViewerCmd
{
public:
    explicit SetViewer(std::size_t id) : id(id) {}
   
    void execute(const Managers& managers) override 
    { 
        managers.viewer_manager->set_active_viewer(id); 
    }
    
private:
    std::size_t id;
};