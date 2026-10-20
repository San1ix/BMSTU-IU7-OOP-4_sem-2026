#include "base_vector.h"

BaseVector::~BaseVector() = default;

bool BaseVector::empty() const noexcept
{
    return container_size == 0;
}

BaseVector::size_type BaseVector::size() const noexcept
{
    return container_size;
}