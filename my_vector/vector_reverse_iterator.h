#pragma once

#include "base_iterator.h"

template <ContainerType T> class Vector;

template <ContainerType T>
class VectorReverseIterator : public BaseIterator<T, false>
{
public:
    using difference_type = typename BaseIterator<T, false>::difference_type;
    using reference = T&;
    using pointer = T*;
    
    VectorReverseIterator() noexcept = default;
    explicit VectorReverseIterator(const Vector<T>& vec) noexcept;
    VectorReverseIterator(const VectorReverseIterator&) noexcept = default;
    ~VectorReverseIterator() override = default;

    VectorReverseIterator& operator++() noexcept;
    VectorReverseIterator operator++(int) noexcept;
    VectorReverseIterator& operator--() noexcept;
    VectorReverseIterator operator--(int) noexcept;
    VectorReverseIterator operator+(difference_type n) const noexcept;
    VectorReverseIterator& operator+=(difference_type n) noexcept;
    VectorReverseIterator operator-(difference_type n) const noexcept;
    VectorReverseIterator& operator-=(difference_type n) noexcept;
    difference_type operator-(const VectorReverseIterator& other) const;

    reference operator[](difference_type n) const;

    friend VectorReverseIterator operator+(difference_type n, const VectorReverseIterator& it) noexcept
    {
        return it + n;
    }

    friend class Vector<T>;

};

