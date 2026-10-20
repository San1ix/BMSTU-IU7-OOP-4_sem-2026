#include "director_solution.h"

#include "director_exception.h"
#include "carcass_director_creator.h"

#include <typeinfo>

DirectorSolution::DirectorSolution()
{
    map = {
        { "carcass", []() { return std::make_shared<CarcassDirectorCreator>(); } }
    };
}

std::shared_ptr<BaseDirectorCreator> DirectorSolution::create_creator(const std::string& type)
{
    auto it = map.find(type);
    if (it != map.end())
        return it->second();
    throw DirectorException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__, (std::string("Unknown director type: ") + type).c_str());
}