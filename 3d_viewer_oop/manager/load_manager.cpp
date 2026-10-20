#include "load_manager.h"

#include "reader_solution.h"
#include "director_solution.h"
#include "builder_solution.h"
#include "carcass_director.h"
#include "manager_exception.h"

#include <typeinfo>

std::shared_ptr<LoadManager> LoadManager::get_instance()
{
    static auto instance = std::shared_ptr<LoadManager>(new LoadManager);
    return instance;
}

void LoadManager::open_file(const std::string& filename)
{
    ReaderSolution rs;
    auto creator = rs.create_creator(filename);
    if (!creator)
        throw LoadManagerException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__, "Failed to create reader creator");
    current_reader = creator->create(filename.c_str());
    if (!current_reader)
        throw LoadManagerException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__, "Failed to create reader");
    current_reader->open();
}

std::shared_ptr<BaseObj> LoadManager::read_model(const std::string& builder_type)
{
    if (!current_reader)
        throw LoadManagerException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__, "No file opened");

    DirectorSolution ds;
    auto dc = ds.create_creator("carcass");
    if (!dc)
        throw LoadManagerWrongDirectorException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__);

    BuilderSolution bs;
    auto builder = bs.create_builder(builder_type);

    auto director = dc->create(builder_type);
    if (auto cd = std::dynamic_pointer_cast<CarcassDirector>(director))
        cd->set_builder(builder);

    loaded_model = director->create(current_reader);
    return loaded_model;
}

void LoadManager::close_file()
{
    if (current_reader && current_reader->is_open())
        current_reader->close();
    current_reader = nullptr;
}