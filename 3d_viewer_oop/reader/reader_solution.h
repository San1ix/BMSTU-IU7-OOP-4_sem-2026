#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "base_reader.h"
#include "base_reader_creator.h"

class ReaderSolution
{
public:
    ReaderSolution();
    ~ReaderSolution() = default;

    std::shared_ptr<BaseReaderCreator> create_creator(const std::string& filename);

private:
    using CreatorFunc = std::function<std::shared_ptr<BaseReaderCreator>()>;
    std::map<std::string, CreatorFunc> map;
};