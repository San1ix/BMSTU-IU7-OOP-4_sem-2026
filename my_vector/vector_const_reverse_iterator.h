#pragma once

#include "base_iterator.h"
#include "vector_reverse_iterator.h"

template <ContainerType T> class Vector;

template <ContainerType T>
class VectorConstReverseIterator : public BaseIterator<T, true>
{

public:
    using difference_type = typename BaseIterator<T, true>::difference_type;
    using reference = const T&;
    using pointer = const T*;
    
    VectorConstReverseIterator() noexcept = default;
    explicit VectorConstReverseIterator(const Vector<T>& vec) noexcept;
    VectorConstReverseIterator(const VectorReverseIterator<T>& other) noexcept;
    VectorConstReverseIterator(const VectorConstReverseIterator&) noexcept = default;
    ~VectorConstReverseIterator() override = default;

    VectorConstReverseIterator& operator++() noexcept;
    VectorConstReverseIterator operator++(int) noexcept;
    VectorConstReverseIterator& operator--() noexcept;
    VectorConstReverseIterator operator--(int) noexcept;
    VectorConstReverseIterator operator+(difference_type n) const noexcept;
    VectorConstReverseIterator& operator+=(difference_type n) noexcept;
    VectorConstReverseIterator operator-(difference_type n) const noexcept;
    VectorConstReverseIterator& operator-=(difference_type n) noexcept;
    difference_type operator-(const VectorConstReverseIterator& other) const;

    reference operator[](difference_type n) const;

    friend VectorConstReverseIterator operator+(difference_type n, const VectorConstReverseIterator& it) noexcept
    {
        return it + n;
    }

    friend class Vector<T>;

};
