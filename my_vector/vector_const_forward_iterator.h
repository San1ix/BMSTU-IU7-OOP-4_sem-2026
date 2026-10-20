#pragma once

#include "base_iterator.h"
#include "vector_forward_iterator.h"

template <ContainerType T> class Vector;

template <ContainerType T>
class VectorConstForwardIterator : public BaseIterator<T, true>
{

public:
    using difference_type = typename BaseIterator<T, true>::difference_type;
    using reference = const T&;
    using pointer = const T*;
    
    VectorConstForwardIterator() noexcept = default;
    explicit VectorConstForwardIterator(const Vector<T>& vec) noexcept;
    VectorConstForwardIterator(const VectorForwardIterator<T>& other) noexcept;
    VectorConstForwardIterator(const VectorConstForwardIterator&) noexcept = default;
    ~VectorConstForwardIterator() override = default;

    VectorConstForwardIterator& operator++() noexcept;
    VectorConstForwardIterator operator++(int) noexcept;
    VectorConstForwardIterator& operator--() noexcept;
    VectorConstForwardIterator operator--(int) noexcept;
    VectorConstForwardIterator operator+(difference_type n) const noexcept;
    VectorConstForwardIterator& operator+=(difference_type n) noexcept;
    VectorConstForwardIterator operator-(difference_type n) const noexcept;
    VectorConstForwardIterator& operator-=(difference_type n) noexcept;
    difference_type operator-(const VectorConstForwardIterator& other) const;

    reference operator[](difference_type n) const;

    friend VectorConstForwardIterator operator+(difference_type n, const VectorConstForwardIterator& it) noexcept
    {
        return it + n;
    }

    friend class Vector<T>;
};

