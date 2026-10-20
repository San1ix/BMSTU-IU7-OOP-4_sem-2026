#pragma once

#include "base_reader_creator.h"
#include "txt_reader.h"

class TxtReaderCreator : public BaseReaderCreator
{
public:
    TxtReaderCreator() = default;
    ~TxtReaderCreator() override = default;

    std::shared_ptr<BaseReader> create(const char* filename) override;
};