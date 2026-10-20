#include "txt_reader.h"

#include "reader_exception.h"
#include <typeinfo>

TxtReader::TxtReader(const char* fn) : filename(fn) {}

TxtReader::~TxtReader()
{
    if (is_open()) 
        close();
}

bool TxtReader::is_open() const 
{ 
    return file.is_open(); 
}

void TxtReader::open()
{
    if (is_open()) 
        return;
    file.open(filename);
    if (!file)
        throw TxtNoFileException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__);
}

void TxtReader::close()
{
    if (!is_open()) 
        return;
    file.close();
}

std::vector<Point> TxtReader::read_points()
{
    if (!is_open()) 
        return {};

    file.clear();
    file.seekg(0, std::ios::beg);

    int count;
    file >> count;

    std::vector<Point> points(count);
    double x, y, z;
    for (int i = 0; i < count; ++i)
    {
        file >> x >> y >> z;
        if (!file)
            throw TxtReadException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__);
        points[i].set(x, y, z);
    }
    return points;
}

std::vector<Edge> TxtReader::read_edges()
{
    if (!is_open()) 
        return {};

    int count;
    file >> count;

    std::vector<Edge> edges(count);
    int first, second;
    for (int i = 0; i < count; ++i)
    {
        file >> first >> second;
        if (!file)
            throw TxtReadException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__);
        edges[i].set(static_cast<std::size_t>(first - 1), static_cast<std::size_t>(second - 1));
    }
    return edges;
}