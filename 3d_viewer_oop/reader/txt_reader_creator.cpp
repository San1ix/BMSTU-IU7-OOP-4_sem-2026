#include "txt_reader_creator.h"

std::shared_ptr<BaseReader> TxtReaderCreator::create(const char* filename)
{
    return std::make_shared<TxtReader>(filename);
}