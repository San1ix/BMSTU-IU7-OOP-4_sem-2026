#include "edge.h"

Edge::Edge(std::size_t first, std::size_t second) : first(first), second(second) {}

std::size_t Edge::get_start() const
{
    return first;
}

std::size_t Edge::get_end() const
{
    return second;
}

void Edge::set_start(std::size_t val)
{
    first = val;
}

void Edge::set_end(std::size_t val)
{
    second = val;
}

void Edge::set(std::size_t first_val, std::size_t second_val)
{
    first = first_val;
    second = second_val;
}

bool Edge::operator==(const Edge& other) const
{
    return (first == other.first && second == other.second) || (first == other.second && second == other.first);
}

bool Edge::operator!=(const Edge& other) const
{
    return !(*this == other);
}