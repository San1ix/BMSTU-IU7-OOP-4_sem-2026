#pragma once

#include "viewer_cmd.h"

class DelViewer : public ViewerCmd
{
public:
    explicit DelViewer(std::size_t id) : id(id) {}

    void execute(const Managers& managers) override 
    { 
        managers.viewer_manager->remove_viewer(id); 
    }
    
private:
    std::size_t id;
};