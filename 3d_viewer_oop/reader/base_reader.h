#pragma once

#include <vector>

#include "point.h"
#include "edge.h"

class BaseReader
{
public:
    BaseReader() = default;
    virtual ~BaseReader() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool is_open() const = 0;
    virtual std::vector<Point> read_points() = 0;
    virtual std::vector<Edge> read_edges() = 0;
};