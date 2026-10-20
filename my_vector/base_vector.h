#pragma once

#include <cstddef>

class BaseVector
{
public:
    using size_type = std::size_t;
    
    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] size_type size() const noexcept;
    
    virtual ~BaseVector() = 0;

protected:
    size_type container_size = 0;
};