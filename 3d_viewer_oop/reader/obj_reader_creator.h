#pragma once

#include "base_reader_creator.h"
#include "obj_reader.h"

class ObjReaderCreator : public BaseReaderCreator
{
public:
    ObjReaderCreator() = default;
    ~ObjReaderCreator() override = default;

    std::shared_ptr<BaseReader> create(const char* filename) override;
};