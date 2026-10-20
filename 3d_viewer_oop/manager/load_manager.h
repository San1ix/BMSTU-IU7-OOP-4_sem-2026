#pragma once

#include <memory>
#include <string>

#include "base_manager.h"
#include "base_reader.h"
#include "base_obj.h"

class LoadManager : public BaseManager
{
public:
    static std::shared_ptr<LoadManager> get_instance();
    LoadManager(const LoadManager&) = delete;
    LoadManager& operator=(const LoadManager&) = delete;

    void open_file(const std::string& filename);
    std::shared_ptr<BaseObj> read_model(const std::string& builder_type);
    void close_file();
    std::shared_ptr<BaseObj> get_loaded_model() const 
    { 
        return loaded_model; 
    }

private:
    LoadManager() = default;
    std::shared_ptr<BaseReader> current_reader;
    std::shared_ptr<BaseObj> loaded_model;
};