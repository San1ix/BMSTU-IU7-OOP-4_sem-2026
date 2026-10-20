#include "obj_reader.h"

#include "reader_exception.h"
#include <sstream>
#include <typeinfo>

ObjReader::ObjReader(const char* fn) : filename(fn) {}

ObjReader::~ObjReader()
{
    if (is_open()) 
        close();
}

bool ObjReader::is_open() const 
{ 
    return file.is_open(); 
}

void ObjReader::open()
{
    if (is_open()) 
        return;
    file.open(filename);
    if (!file)
        throw ObjNoFileException(__TIME__, __FILE__, __LINE__, typeid(*this).name(), __FUNCTION__);
}

void ObjReader::close()
{
    if (!is_open()) 
        return;
    file.close();
}

std::vector<Point> ObjReader::read_points()
{
    if (!is_open()) 
        return {};

    file.clear();
    file.seekg(0, std::ios::beg);

    std::vector<Point> points;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') 
            continue;
        
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if (prefix == "v")
        {
            double x, y, z;
            if (iss >> x >> y >> z)
                points.emplace_back(x, y, z);
        }
    }
    return points;
}

std::vector<Edge> ObjReader::read_edges()
{
    if (!is_open()) 
        return {};

    file.clear();
    file.seekg(0, std::ios::beg);

    std::vector<Edge> edges;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') 
            continue;

        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;
        if (prefix == "l")
        {
            int first, second;
            if (iss >> first >> second)
                edges.emplace_back(static_cast<std::size_t>(first - 1), static_cast<std::size_t>(second - 1));
        }
    }
    return edges;
}