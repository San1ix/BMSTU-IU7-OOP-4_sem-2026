#pragma once

#include "base_iterator.h"

template <ContainerType T, bool IsConst>
typename BaseIterator<T, IsConst>::reference BaseIterator<T, IsConst>::operator*() const
{
    check_index(__PRETTY_FUNCTION__);
    check_vector(__PRETTY_FUNCTION__);
    return *get_ptr_cur();
}

template <ContainerType T, bool IsConst>
typename BaseIterator<T, IsConst>::pointer BaseIterator<T, IsConst>::operator->() const
{
    check_index(__PRETTY_FUNCTION__);
    check_vector(__PRETTY_FUNCTION__);
    return get_ptr_cur();
}

template <ContainerType T, bool IsConst>
bool BaseIterator<T, IsConst>::operator==(const BaseIterator& other) const
{
    check_iters(other.piter, __PRETTY_FUNCTION__);
    return index == other.index;
}

template <ContainerType T, bool IsConst>
bool BaseIterator<T, IsConst>::operator!=(const BaseIterator& other) const
{
    return !(*this == other);
}

template <ContainerType T, bool IsConst>
std::strong_ordering BaseIterator<T, IsConst>::operator<=>(const BaseIterator& other) const
{
    check_iters(other.piter, __PRETTY_FUNCTION__);
    return index <=> other.index;
}

template <ContainerType T, bool IsConst>
void BaseIterator<T, IsConst>::check_vector(const char* func_name) const
{
    if (piter.expired())
        throw errDeletedVector(__FILE__, __LINE__, func_name);
}

template <ContainerType T, bool IsConst>
void BaseIterator<T, IsConst>::check_index(const char* func_name) const
{
    if (index < 0 || index >= size)
        throw errIndexOutOfRange(__FILE__, __LINE__, func_name);
}

template <ContainerType T, bool IsConst>
void BaseIterator<T, IsConst>::check_iters(std::weak_ptr<T[]> other, const char* func_name) const
{
    if (other.lock() != piter.lock())
        throw errDifferentVectors(__FILE__, __LINE__, func_name);
}

template <ContainerType T, bool IsConst>
typename BaseIterator<T, IsConst>::pointer BaseIterator<T, IsConst>::get_ptr_cur() const
{
    return piter.lock().get() + index;
}

template <ContainerType T, bool IsConst>
BaseIterator<T, IsConst>::operator bool() const noexcept
{
    return !piter.expired() && index >= 0 && index < size;
}