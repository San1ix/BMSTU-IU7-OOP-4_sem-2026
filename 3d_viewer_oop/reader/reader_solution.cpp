#include "reader_solution.h"

#include "txt_reader_creator.h"
#include "obj_reader_creator.h"

#include "reader_exception.h"
#include <filesystem>
#include <typeinfo>

ReaderSolution::ReaderSolution()
{
    map = {
        { ".txt", []() { return std::make_shared<TxtReaderCreator>(); } },
        { ".obj", []() { return std::make_shared<ObjReaderCreator>(); } }
    };
}

std::shared_ptr<BaseReaderCreator> ReaderSolution::create_creator(const std::string& filename)
{
    std::string ext = std::filesystem::path(filename).extension().string();
    auto it = map.find(ext);
    if (it != map.end())
        return it->second();
    throw ReaderException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__, "Unsupported file extension");
}