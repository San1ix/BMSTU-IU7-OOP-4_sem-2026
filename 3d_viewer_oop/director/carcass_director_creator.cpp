#include "carcass_director_creator.h"

std::shared_ptr<BaseDirector> CarcassDirectorCreator::create(const std::string& type)
{
    auto director = std::make_shared<CarcassDirector>();
    BuilderSolution builder_solution;
    director->set_builder(builder_solution.create_builder(type));
    return director;
}