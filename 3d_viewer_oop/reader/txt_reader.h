#pragma once

#include "base_reader.h"

#include <fstream>

class TxtReader : public BaseReader
{
public:
    explicit TxtReader(const char* filename);
    ~TxtReader() override;

    void open() override;
    void close() override;
    bool is_open() const override;
    std::vector<Point> read_points() override;
    std::vector<Edge> read_edges() override;

private:
    std::string filename;
    std::ifstream file;
};