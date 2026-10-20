#include "carcass_director.h"

#include "carcass_model.h"
#include "carcass_model_impl.h"
#include "list_builder.h"
#include "matrix_builder.h"

void CarcassDirector::set_builder(std::shared_ptr<BaseBuilder> b) { builder = b; }

std::shared_ptr<BaseObj> CarcassDirector::create(std::shared_ptr<BaseReader> reader)
{
    if (!reader->is_open())
        reader->open();

    auto points = reader->read_points();
    auto edges = reader->read_edges();
    reader->close();

    builder->build_points(points);
    builder->build_edges(edges);
    builder->build_center();

    auto structure = builder->get_structure();
    auto impl = std::make_shared<CarcassModelImpl>(structure);
    return std::make_shared<CarcassModel>(impl);
}