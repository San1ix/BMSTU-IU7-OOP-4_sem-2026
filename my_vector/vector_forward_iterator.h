#pragma once

#include "base_iterator.h"

template <ContainerType T> class Vector;

template <ContainerType T>
class VectorForwardIterator : public BaseIterator<T, false>
{
public:
    using difference_type = typename BaseIterator<T, false>::difference_type;
    using reference = T&;
    using pointer = T*;
    
    VectorForwardIterator() noexcept = default;
    explicit VectorForwardIterator(const Vector<T>& vec) noexcept;
    VectorForwardIterator(const VectorForwardIterator&) noexcept = default;
    ~VectorForwardIterator() override = default;

    VectorForwardIterator& operator++() noexcept;
    VectorForwardIterator operator++(int) noexcept;
    VectorForwardIterator& operator--() noexcept;
    VectorForwardIterator operator--(int) noexcept;
    VectorForwardIterator operator+(difference_type n) const noexcept;
    VectorForwardIterator& operator+=(difference_type n) noexcept;
    VectorForwardIterator operator-(difference_type n) const noexcept;
    VectorForwardIterator& operator-=(difference_type n) noexcept;
    difference_type operator-(const VectorForwardIterator& other) const;

    reference operator[](difference_type n) const;

    friend VectorForwardIterator operator+(difference_type n, const VectorForwardIterator& it) noexcept
    {
        return it + n;
    }

    friend class Vector<T>;

};

