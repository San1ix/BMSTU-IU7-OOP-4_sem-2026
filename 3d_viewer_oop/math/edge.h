#pragma once

#include <cstddef>

class Edge
{
public:
    Edge() = default;
    Edge(std::size_t first, std::size_t second);
    Edge(const Edge& other) = default;
    Edge(Edge&& other) noexcept = default;

    Edge& operator=(const Edge& other) = default;
    Edge& operator=(Edge&& other) noexcept = default;

    ~Edge() = default;

    std::size_t get_start() const;
    std::size_t get_end() const;

    void set_start(std::size_t val);
    void set_end(std::size_t val);
    void set(std::size_t first_val, std::size_t second_val);

    bool operator==(const Edge& other) const;
    bool operator!=(const Edge& other) const;

private:
    std::size_t first = 0;
    std::size_t second = 0;
};