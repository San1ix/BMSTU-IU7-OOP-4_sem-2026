#pragma once

#include <iterator>
#include <memory>
#include <compare>
#include "vector_concepts.h"
#include "iterator_exceptions.h"

template <ContainerType T, bool IsConst>
class BaseIterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using reference = std::conditional_t<IsConst, const T&, T&>;
    using pointer = std::conditional_t<IsConst, const T*, T*>;

    BaseIterator() noexcept = default;
    virtual ~BaseIterator() = default;

    reference operator*() const;
    pointer operator->() const;
    
    bool operator==(const BaseIterator& other) const;
    bool operator!=(const BaseIterator& other) const;
    std::strong_ordering operator<=>(const BaseIterator& other) const;
    explicit operator bool() const noexcept;

protected:
    void check_vector(const char* func_name) const;
    void check_index(const char* func_name) const;
    void check_iters(std::weak_ptr<T[]> other, const char* func_name) const;

    pointer get_ptr_cur() const;
    
    std::weak_ptr<T[]> piter;
    difference_type size = 0;
    difference_type index = 0;
};