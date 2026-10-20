#include "obj_reader_creator.h"

std::shared_ptr<BaseReader> ObjReaderCreator::create(const char* filename)
{
    return std::make_shared<ObjReader>(filename);
}