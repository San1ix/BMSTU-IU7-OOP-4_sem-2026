#include "builder_solution.h"

#include "list_builder.h"
#include "matrix_builder.h"

BuilderSolution::BuilderSolution()
{
    map = {
        { "list",   []() { return std::make_shared<ListBuilder>(); } },
        { "matrix", []() { return std::make_shared<MatrixBuilder>(); } }
    };
}

std::shared_ptr<BaseBuilder> BuilderSolution::create_builder(const std::string& type)
{
    auto it = map.find(type);
    if (it != map.end())
        return it->second();
    return std::make_shared<ListBuilder>();
}