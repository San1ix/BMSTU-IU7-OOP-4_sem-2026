#pragma once

#include "base_reader.h"

#include <fstream>

class ObjReader : public BaseReader
{
public:
    explicit ObjReader(const char* filename);
    ~ObjReader() override;

    void open() override;
    void close() override;
    bool is_open() const override;
    std::vector<Point> read_points() override;
    std::vector<Edge> read_edges() override;

private:
    std::string filename;
    std::ifstream file;
};