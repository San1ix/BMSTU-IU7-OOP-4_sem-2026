#pragma once

#include "vector.h"
#include "base_iterator.hpp"
#include "vector_exceptions.h"
#include <ranges>
#include <cmath>
#include <algorithm> // Для std::ranges::fold_left

#define EPS 1e-6

template <ContainerType T>
VectorForwardIterator<T>::VectorForwardIterator(const Vector<T>& vec) noexcept
{
    this->piter = vec.container;
    this->size = vec.size();
    this->index = 0;
}

template <ContainerType T>
VectorForwardIterator<T>& VectorForwardIterator<T>::operator++() noexcept
{
    ++this->index;
    return *this;
}

template <ContainerType T>
VectorForwardIterator<T> VectorForwardIterator<T>::operator++(int) noexcept
{
    VectorForwardIterator tmp = *this;
    ++this->index;
    return tmp;
}

template <ContainerType T>
VectorForwardIterator<T>& VectorForwardIterator<T>::operator--() noexcept
{
    --this->index;
    return *this;
}

template <ContainerType T>
VectorForwardIterator<T> VectorForwardIterator<T>::operator--(int) noexcept
{
    VectorForwardIterator tmp = *this;
    --this->index;
    return tmp;
}

template <ContainerType T>
VectorForwardIterator<T> VectorForwardIterator<T>::operator+(difference_type n) const noexcept
{
    VectorForwardIterator tmp = *this;
    tmp.index += n;
    return tmp;
}

template <ContainerType T>
VectorForwardIterator<T>& VectorForwardIterator<T>::operator+=(difference_type n) noexcept
{
    this->index += n;
    return *this;
}

template <ContainerType T>
VectorForwardIterator<T> VectorForwardIterator<T>::operator-(difference_type n) const noexcept
{
    VectorForwardIterator tmp = *this;
    tmp.index -= n;
    return tmp;
}

template <ContainerType T>
VectorForwardIterator<T>& VectorForwardIterator<T>::operator-=(difference_type n) noexcept
{
    this->index -= n;
    return *this;
}

template <ContainerType T>
typename VectorForwardIterator<T>::difference_type VectorForwardIterator<T>::operator-(const VectorForwardIterator& other) const
{
    this->check_iters(other.piter, __PRETTY_FUNCTION__);
    return this->index - other.index;
}

template <ContainerType T>
typename VectorForwardIterator<T>::reference VectorForwardIterator<T>::operator[](difference_type n) const
{
    return *(*this + n);
}

template <ContainerType T>
VectorConstForwardIterator<T>::VectorConstForwardIterator(const Vector<T>& vec) noexcept
{
    this->piter = vec.container;
    this->size = vec.size();
    this->index = 0;
}

template <ContainerType T>
VectorConstForwardIterator<T>::VectorConstForwardIterator(const VectorForwardIterator<T>& other) noexcept
{
    this->piter = other.piter;
    this->size = other.size;
    this->index = other.index;
}

template <ContainerType T>
VectorConstForwardIterator<T>& VectorConstForwardIterator<T>::operator++() noexcept
{
    ++this->index;
    return *this;
}

template <ContainerType T>
VectorConstForwardIterator<T> VectorConstForwardIterator<T>::operator++(int) noexcept
{
    VectorConstForwardIterator tmp = *this;
    ++this->index;
    return tmp;
}

template <ContainerType T>
VectorConstForwardIterator<T>& VectorConstForwardIterator<T>::operator--() noexcept
{
    --this->index;
    return *this;
}

template <ContainerType T>
VectorConstForwardIterator<T> VectorConstForwardIterator<T>::operator--(int) noexcept
{
    VectorConstForwardIterator tmp = *this;
    --this->index;
    return tmp;
}

template <ContainerType T>
VectorConstForwardIterator<T> VectorConstForwardIterator<T>::operator+(difference_type n) const noexcept
{
    VectorConstForwardIterator tmp = *this;
    tmp.index += n;
    return tmp;
}

template <ContainerType T>
VectorConstForwardIterator<T>& VectorConstForwardIterator<T>::operator+=(difference_type n) noexcept
{
    this->index += n;
    return *this;
}

template <ContainerType T>
VectorConstForwardIterator<T> VectorConstForwardIterator<T>::operator-(difference_type n) const noexcept
{
    VectorConstForwardIterator tmp = *this;
    tmp.index -= n;
    return tmp;
}

template <ContainerType T>
VectorConstForwardIterator<T>& VectorConstForwardIterator<T>::operator-=(difference_type n) noexcept
{
    this->index -= n;
    return *this;
}

template <ContainerType T>
typename VectorConstForwardIterator<T>::difference_type VectorConstForwardIterator<T>::operator-(const VectorConstForwardIterator& other) const
{
    this->check_iters(other.piter, __PRETTY_FUNCTION__);
    return this->index - other.index;
}

template <ContainerType T>
typename VectorConstForwardIterator<T>::reference VectorConstForwardIterator<T>::operator[](difference_type n) const
{
    return *(*this + n);
}

template <ContainerType T>
VectorReverseIterator<T>::VectorReverseIterator(const Vector<T>& vec) noexcept
{
    this->piter = vec.container;
    this->size = vec.size();
    this->index = static_cast<std::ptrdiff_t>(this->size) - 1;
}

template <ContainerType T>
VectorReverseIterator<T>& VectorReverseIterator<T>::operator++() noexcept
{
    --this->index;
    return *this;
}

template <ContainerType T>
VectorReverseIterator<T> VectorReverseIterator<T>::operator++(int) noexcept
{
    VectorReverseIterator tmp = *this;
    --this->index;
    return tmp;
}

template <ContainerType T>
VectorReverseIterator<T>& VectorReverseIterator<T>::operator--() noexcept
{
    ++this->index;
    return *this;
}

template <ContainerType T>
VectorReverseIterator<T> VectorReverseIterator<T>::operator--(int) noexcept
{
    VectorReverseIterator tmp = *this;
    ++this->index;
    return tmp;
}

template <ContainerType T>
VectorReverseIterator<T> VectorReverseIterator<T>::operator+(difference_type n) const noexcept
{
    VectorReverseIterator tmp = *this;
    tmp.index -= n;
    return tmp;
}

template <ContainerType T>
VectorReverseIterator<T>& VectorReverseIterator<T>::operator+=(difference_type n) noexcept
{
    this->index -= n;
    return *this;
}

template <ContainerType T>
VectorReverseIterator<T> VectorReverseIterator<T>::operator-(difference_type n) const noexcept
{
    VectorReverseIterator tmp = *this;
    tmp.index += n;
    return tmp;
}

template <ContainerType T>
VectorReverseIterator<T>& VectorReverseIterator<T>::operator-=(difference_type n) noexcept
{
    this->index -= n;
    return *this;
}

template <ContainerType T>
typename VectorReverseIterator<T>::difference_type VectorReverseIterator<T>::operator-(const VectorReverseIterator& other) const
{
    this->check_iters(other.piter, __PRETTY_FUNCTION__);
    return other.index - this->index;
}

template <ContainerType T>
typename VectorReverseIterator<T>::reference VectorReverseIterator<T>::operator[](difference_type n) const
{
    return *(*this + n);
}

template <ContainerType T>
VectorConstReverseIterator<T>::VectorConstReverseIterator(const Vector<T>& vec) noexcept
{
    this->piter = vec.container;
    this->size = vec.size();
    this->index = static_cast<std::ptrdiff_t>(this->size) - 1;
}

template <ContainerType T>
VectorConstReverseIterator<T>::VectorConstReverseIterator(const VectorReverseIterator<T>& other) noexcept
{
    this->piter = other.piter;
    this->size = other.size;
    this->index = other.index;
}

template <ContainerType T>
VectorConstReverseIterator<T>& VectorConstReverseIterator<T>::operator++() noexcept
{
    --this->index;
    return *this;
}

template <ContainerType T>
VectorConstReverseIterator<T> VectorConstReverseIterator<T>::operator++(int) noexcept
{
    VectorConstReverseIterator tmp = *this;
    --this->index;
    return tmp;
}

template <ContainerType T>
VectorConstReverseIterator<T>& VectorConstReverseIterator<T>::operator--() noexcept
{
    --this->index;
    return *this;
}

template <ContainerType T>
VectorConstReverseIterator<T> VectorConstReverseIterator<T>::operator--(int) noexcept
{
    VectorConstReverseIterator tmp = *this;
    --this->index;
    return tmp;
}

template <ContainerType T>
VectorConstReverseIterator<T> VectorConstReverseIterator<T>::operator+(difference_type n) const noexcept
{
    VectorConstReverseIterator tmp = *this;
    tmp.index -= n;
    return tmp;
}

template <ContainerType T>
VectorConstReverseIterator<T>& VectorConstReverseIterator<T>::operator+=(difference_type n) noexcept
{
    this->index -= n;
    return *this;
}

template <ContainerType T>
VectorConstReverseIterator<T> VectorConstReverseIterator<T>::operator-(difference_type n) const noexcept
{
    VectorConstReverseIterator tmp = *this;
    tmp.index += n;
    return tmp;
}

template <ContainerType T>
VectorConstReverseIterator<T>& VectorConstReverseIterator<T>::operator-=(difference_type n) noexcept
{
    this->index += n;
    return *this;
}

template <ContainerType T>
typename VectorConstReverseIterator<T>::difference_type VectorConstReverseIterator<T>::operator-(const VectorConstReverseIterator& other) const
{
    this->check_iters(other.piter, __PRETTY_FUNCTION__);
    return other.index - this->index;
}

template <ContainerType T>
typename VectorConstReverseIterator<T>::reference VectorConstReverseIterator<T>::operator[](difference_type n) const
{
    return *(*this + n);
}

template <ContainerType T>
Vector<T>::Vector()
{
    container_size = 0;
    memory_allocation(container_size, __PRETTY_FUNCTION__);
}

template <ContainerType T>
Vector<T>::Vector(const Vector<T>& other)
{
    container_size = other.size();
    memory_allocation(container_size, __PRETTY_FUNCTION__);
    std::ranges::copy(other, begin());
}

template <ContainerType T>
Vector<T>::Vector(Vector<T>&& other) noexcept
{
    container_size = std::exchange(other.container_size, 0);
    container = std::move(other.container);
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>::Vector(const Vector<U>& other)
{
    container_size = other.size();
    memory_allocation(container_size, __PRETTY_FUNCTION__);
    std::ranges::copy(other, begin());
}

template <ContainerType T>
template <CopyableContainer<T> Cont>
Vector<T>::Vector(const Cont& other)
{
    container_size = other.size();
    memory_allocation(container_size, __PRETTY_FUNCTION__);
    std::ranges::copy(other, begin());
}

template <ContainerType T>
Vector<T>::Vector(BaseVector::size_type size)
{
    container_size = size;
    memory_allocation(size, __PRETTY_FUNCTION__);
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>::Vector(std::initializer_list<U> arr)
{
    container_size = arr.size();
    memory_allocation(container_size, __PRETTY_FUNCTION__);
    std::ranges::copy(arr, begin());
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>::Vector(BaseVector::size_type size, const U* arr)
{
    check_arr_null(arr, __PRETTY_FUNCTION__);
    container_size = size;
    memory_allocation(container_size, __PRETTY_FUNCTION__);
    std::ranges::copy(arr, arr + size, begin());
}

template <ContainerType T>
template <CompatibleIterator<T> I, SentinelIter<I> S>
Vector<T>::Vector(I beg, S end)
{
    auto d = std::ranges::distance(beg, end);
    container_size = static_cast<BaseVector::size_type>(d);
    memory_allocation(container_size, __PRETTY_FUNCTION__);
    std::ranges::copy(beg, end, begin());
}

template <ContainerType T>
template <ConvertibleRange<T> R>
Vector<T>::Vector(const R& r)
{
    auto d = std::ranges::distance(r);
    container_size = static_cast<BaseVector::size_type>(d);
    memory_allocation(container_size, __PRETTY_FUNCTION__);
    std::ranges::copy(std::ranges::begin(r), std::ranges::end(r), begin());
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>& Vector<T>::operator=(const std::initializer_list<U> arr)
{
    Vector<T> tmp(arr);
    std::swap(container_size, tmp.container_size);
    std::swap(container, tmp.container);
    return *this;
}

template <ContainerType T>
template <CopyableContainer<T> Con>
Vector<T>& Vector<T>::operator=(const Con& other)
{
    Vector<T> tmp(other);
    std::swap(container_size, tmp.container_size);
    std::swap(container, tmp.container);
    return *this;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>& Vector<T>::operator=(const Vector<U>& other)
{
    Vector<T> tmp(other);
    std::swap(container_size, tmp.container_size);
    std::swap(container, tmp.container);
    return *this;
}

template <ContainerType T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
    if (this != &other)
    {
        container_size = std::exchange(other.container_size, 0);
        container = std::move(other.container);
    }
    return *this;
}

template <ContainerType T>
template <SummableContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> Vector<T>::operator+(const Con& other) const
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, typename Con::value_type>> result(size());
    std::ranges::transform(*this, other, result.begin(), [](const auto& a, const auto& b) {return a + b;});
    return result;
}

template <ContainerType T>
template <SummableContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> Vector<T>::sum(const Con& other) const
{
    return *this + other;
}

template <ContainerType T>
template <Summable<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::operator+(const Vector<U>& other) const
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, U>> result(size());
    std::ranges::transform(*this, other, result.begin(), [](const auto& a, const auto& b) {return a + b;});
    return result;
}

template <ContainerType T>
template <Summable<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::sum(const Vector<U>& other) const
{
    return *this + other;
}

/*
template <ContainerType T>
template <SummableScalar<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::operator+(const U& num) const
{
    Vector<std::common_type_t<T, U>> result(size());
    std::ranges::transform(*this, result.begin(), [&num](const auto& el) { return el + num; });
    return result;
}

template <ContainerType T>
template <SummableScalar<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::plus(const U& num) const
{
    return *this + num;
}
*/

template <ContainerType T>
template <SummableEqContainer<T> Con>
Vector<T>& Vector<T>::operator+=(const Con& other)
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    std::ranges::transform(*this, other, begin(), [](const auto& a, const auto& b) {return a + b;});
    return *this;
}

template <ContainerType T>
template <SummableEqContainer<T> Con>
Vector<T>& Vector<T>::sum_eq(const Con& other)
{
    return *this += other;
}

template <ContainerType T>
template <SummableEq<T> U>
Vector<T>& Vector<T>::operator+=(const Vector<U>& other)
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    std::ranges::transform(*this, other, begin(), [](const auto& a, const auto& b) {return a + b;});
    return *this;
}

template <ContainerType T>
template <SummableEq<T> U>
Vector<T>& Vector<T>::sum_eq(const Vector<U>& other)
{
    return *this += other;
}

/*
template <ContainerType T>
template <SummableEqScalar<T> U>
Vector<T>& Vector<T>::operator+=(const U& num)
{
    std::ranges::transform(*this, begin(), [&num](const auto& el) { return el + num; });
    return *this;
}

template <ContainerType T>
template <SummableEqScalar<T> U>
Vector<T>& Vector<T>::plus_eq(const U& num)
{
    return *this += num;
}
*/

template <ContainerType T>
template <SubtractableContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> Vector<T>::operator-(const Con& other) const
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, typename Con::value_type>> result(size());
    std::ranges::transform(*this, other, result.begin(), [](const auto& a, const auto& b) {return a - b;});
    return result;
}

template <ContainerType T>
template <SubtractableContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> Vector<T>::sub(const Con& other) const
{
    return *this - other;
}

template <ContainerType T>
template <Subtractable<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::operator-(const Vector<U>& other) const
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, U>> result(size());
    std::ranges::transform(*this, other, result.begin(), [](const auto& a, const auto& b) {return a - b;});
    return result;
}

template <ContainerType T>
template <Subtractable<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::sub(const Vector<U>& other) const
{
    return *this - other;
}

/*
template <ContainerType T>
template <SubtractableScalar<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::operator-(const U& num) const
{
    Vector<std::common_type_t<T, U>> result(size());
    std::ranges::transform(*this, result.begin(), [&num](const auto& el) { return el - num; });
    return result;
}

template <ContainerType T>
template <SubtractableScalar<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::minus(const U& num) const
{
    return *this - num;
}
*/

template <ContainerType T>
template <SubtractableEqContainer<T> Con>
Vector<T>& Vector<T>::operator-=(const Con& other)
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    std::ranges::transform(*this, other, begin(), [](const auto& a, const auto& b) {return a - b;});
    return *this;
}

template <ContainerType T>
template <SubtractableEqContainer<T> Con>
Vector<T>& Vector<T>::sub_eq(const Con& other)
{
    return *this -= other;
}

template <ContainerType T>
template <SubtractableEq<T> U>
Vector<T>& Vector<T>::operator-=(const Vector<U>& other)
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    std::ranges::transform(*this, other, begin(), [](const auto& a, const auto& b) {return a - b;});
    return *this;
}

template <ContainerType T>
template <SubtractableEq<T> U>
Vector<T>& Vector<T>::sub_eq(const Vector<U>& other)
{
    return *this -= other;
}

/*
template <ContainerType T>
template <SubtractableEqScalar<T> U>
Vector<T>& Vector<T>::operator-=(const U& num)
{
    std::ranges::transform(*this, begin(), [&num](const auto& el) { return el - num; });
    return *this;
}

template <ContainerType T>
template <SubtractableEqScalar<T> U>
Vector<T>& Vector<T>::minus_eq(const U& num)
{
    return *this -= num;
}
*/

template <ContainerType T>
Vector<T> Vector<T>::operator-() const
    requires Negatable<T>
{
    Vector<T> result(*this);
    std::ranges::transform(result, result.begin(), [](const auto& el) {return -el;});
    return result;
}

template <ContainerType T>
Vector<T> Vector<T>::neg() const
    requires Negatable<T>
{
    return -(*this);
}

template <ContainerType T>
template <MultipliableContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> Vector<T>::operator*(const Con& other) const
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, typename Con::value_type>> result(size());
    std::ranges::transform(*this, other, result.begin(), [](const auto& a, const auto& b) {return a * b;});
    return result;
}

template <ContainerType T>
template <MultipliableContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> Vector<T>::mul(const Con& other) const
{
    return *this * other;
}

template <ContainerType T>
template <Multipliable<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::operator*(const Vector<U>& other) const
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, U>> result(size());
    std::ranges::transform(*this, other, result.begin(), [](const auto& a, const auto& b) {return a * b;});
    return result;
}

template <ContainerType T>
template <Multipliable<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::mul(const Vector<U>& other) const
{
    return *this * other;
}

template <ContainerType T>
template <MultipliableScalar<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::operator*(const U& num) const
{
    Vector<std::common_type_t<T, U>> result(size());
    std::ranges::transform(*this, result.begin(), [&num](const auto &el) {return el * num;});
    return result;
}

template <ContainerType T>
template <MultipliableScalar<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::mul(const U& num) const
{
    return *this * num;
}

template <ContainerType T>
template <MultipliableEqContainer<T> Con>
Vector<T>& Vector<T>::operator*=(const Con& other)
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    std::ranges::transform(*this, other, begin(), [](const auto& a, const auto& b) {return a * b;});
    return *this;
}

template <ContainerType T>
template <MultipliableEqContainer<T> Con>
Vector<T>& Vector<T>::mul_eq(const Con& other)
{
    return *this *= other;
}

template <ContainerType T>
template <MultipliableEq<T> U>
Vector<T>& Vector<T>::operator*=(const Vector<U>& other)
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    std::ranges::transform(*this, other, begin(), [](const auto& a, const auto& b) {return a * b;}); // Исправлено вычитание на умножение
    return *this;
}

template <ContainerType T>
template <MultipliableEq<T> U>
Vector<T>& Vector<T>::mul_eq(const Vector<U>& other)
{
    return *this *= other;
}

template <ContainerType T>
template <MultipliableEqScalar<T> U>
Vector<T>& Vector<T>::operator*=(const U& num)
{
    std::ranges::transform(*this, begin(), [&num](const auto &el) {return el * num;});
    return *this;
}

template <ContainerType T>
template <MultipliableEqScalar<T> U>
Vector<T>& Vector<T>::mul_eq(const U& num)
{
    return *this *= num;
}

template <ContainerType T>
template <DivisibleContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> Vector<T>::operator/(const Con& other) const
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, typename Con::value_type>> result(size());
    std::ranges::transform(*this, other, result.begin(), [this](const auto& a, const auto& b) {check_division_zero(b, __PRETTY_FUNCTION__); return a / b;});
    return result;
}

template <ContainerType T>
template <DivisibleContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> Vector<T>::div(const Con& other) const
{
    return *this / other;
}

template <ContainerType T>
template <Divisible<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::operator/(const Vector<U>& other) const
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, U>> result(size());
    std::ranges::transform(*this, other, result.begin(), [this](const auto& a, const auto& b) {check_division_zero(b, __PRETTY_FUNCTION__); return a / b;});
    return result;
}

template <ContainerType T>
template <Divisible<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::div(const Vector<U>& other) const
{
    return *this / other;
}

template <ContainerType T>
template <DivisibleScalar<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::operator/(const U& num) const
{
    check_division_zero(num, __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, U>> result(size());
    std::ranges::transform(*this, result.begin(), [&num](const auto &el) {return el / num;});
    return result;
}

template <ContainerType T>
template <DivisibleScalar<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::div(const U& num) const
{
    return *this / num;
}

template <ContainerType T>
template <DivisibleEqContainer<T> Con>
Vector<T>& Vector<T>::operator/=(const Con& other)
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    std::ranges::transform(*this, other, begin(), [this](const auto& a, const auto& b) {check_division_zero(b, __PRETTY_FUNCTION__); return a / b;});
    return *this;
}

template <ContainerType T>
template <DivisibleEqContainer<T> Con>
Vector<T>& Vector<T>::div_eq(const Con& other)
{
    return *this /= other;
}

template <ContainerType T>
template <DivisibleEq<T> U>
Vector<T>& Vector<T>::operator/=(const Vector<U>& other)
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    std::ranges::transform(*this, other, begin(), [this](const auto& a, const auto& b) {check_division_zero(b, __PRETTY_FUNCTION__); return a / b;});
    return *this;
}

template <ContainerType T>
template <DivisibleEq<T> U>
Vector<T>& Vector<T>::div_eq(const Vector<U>& other)
{
    return *this /= other;
}

template <ContainerType T>
template <DivisibleEqScalar<T> U>
Vector<T>& Vector<T>::operator/=(const U& num)
{
    check_division_zero(num, __PRETTY_FUNCTION__);
    std::ranges::transform(*this, begin(), [&num](const auto &el) {return el / num;});
    return *this;
}

template <ContainerType T>
template <DivisibleEqScalar<T> U>
Vector<T>& Vector<T>::div_eq(const U& num)
{
    return *this /= num;
}

template <ContainerType T>
template <OperationableContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> Vector<T>::operator^(const Con& other) const
{
    check_size_3(__PRETTY_FUNCTION__);
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, typename Con::value_type>> result(3);
    result[0] = (*this)[1] * other[2] - (*this)[2] * other[1];
    result[1] = (*this)[2] * other[0] - (*this)[0] * other[2];
    result[2] = (*this)[0] * other[1] - (*this)[1] * other[0];
    return result;
}

template <ContainerType T>
template <OperationableContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> Vector<T>::vec_mul(const Con& other) const
{
    return *this ^ other;
}

template <ContainerType T>
template <Operationable<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::operator^(const Vector<U>& other) const
{
    check_size_3(__PRETTY_FUNCTION__);
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    Vector<std::common_type_t<T, U>> result(3);
    result[0] = (*this)[1] * other[2] - (*this)[2] * other[1];
    result[1] = (*this)[2] * other[0] - (*this)[0] * other[2];
    result[2] = (*this)[0] * other[1] - (*this)[1] * other[0];
    return result;
}

template <ContainerType T>
template <Operationable<T> U>
Vector<std::common_type_t<T, U>> Vector<T>::vec_mul(const Vector<U>& other) const
{
    return *this ^ other;
}

template <ContainerType T>
template <OperationableContainer<T> Con>
Vector<T>& Vector<T>::vec_mul_eq(const Con& other)
{
    return *this ^= other;
}

template <ContainerType T>
template <Operationable<T> U>
Vector<T>& Vector<T>::operator^=(const Vector<U>& other)
{
    *this = *this ^ other;
    return *this;
}

template <ContainerType T>
template <Operationable<T> U>
Vector<T>& Vector<T>::vec_mul_eq(const Vector<U>& other)
{
    return *this ^= other;
}

template <ContainerType T>
template <Operationable<T> U>
double Vector<T>::operator&(const Vector<U>& other) const
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    
    auto other_it = other.begin();
    return std::ranges::fold_left(*this, 0.0, [&other_it](double acc, const auto& val) 
    {
        double prod = static_cast<double>(val) * static_cast<double>(*other_it);
        ++other_it;
        return acc + prod;
    });
}

template <ContainerType T>
template <Operationable<T> U>
double Vector<T>::scalar_mul(const Vector<U>& other) const
{
    return *this & other;
}

template <ContainerType T>
typename Vector<T>::reference Vector<T>::operator[](BaseVector::size_type index)
{
    return get_item(index);
}

template <ContainerType T>
typename Vector<T>::const_reference Vector<T>::operator[](BaseVector::size_type index) const
{
    return get_item(index);
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>& Vector<T>::set_item(BaseVector::size_type index, const U& elem)
{
    check_index(index, __PRETTY_FUNCTION__);
    get_item(index) = elem;
    return *this;
}

template <ContainerType T>
typename Vector<T>::reference Vector<T>::get_item(BaseVector::size_type index)
{
    check_index(index, __PRETTY_FUNCTION__);
    return container[index];
}

template <ContainerType T>
typename Vector<T>::const_reference Vector<T>::get_item(BaseVector::size_type index) const
{
    check_index(index, __PRETTY_FUNCTION__);
    return container[index];
}

template <ContainerType T>
double Vector<T>::len() const
{
    double sum = std::ranges::fold_left(*this, 0.0, [](double acc, const auto& val) {return acc + static_cast<double>(val) * static_cast<double>(val);});
    return std::sqrt(sum);
}

template <ContainerType T>
Vector<double> Vector<T>::normalization() const
{
    double l = len();
    check_division_zero(l, __PRETTY_FUNCTION__);
    Vector<double> result(size());
    std::ranges::transform(*this, result.begin(), [l](const auto& elem) { return elem / l; });
    return result;
}

template <ContainerType T>
bool Vector<T>::is_normalize() const
{
    return std::abs(len() - 1.0) < EPS;
}

template <ContainerType T>
bool Vector<T>::is_zero() const
{
    return std::abs(len()) < EPS;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
double Vector<T>::calc_angle(const Vector<U>& other) const
{
    check_size_equal(other.size(), __PRETTY_FUNCTION__);
    double mul_len = len() * other.len();
    check_division_zero(mul_len, __PRETTY_FUNCTION__);
    return std::acos(scalar_mul(other) / mul_len);
}

template <ContainerType T>
template <ConvertAssignable<T> U>
bool Vector<T>::is_collinear(const Vector<U>& other) const
{
    return std::abs(calc_angle(other)) < EPS;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
bool Vector<T>::is_orthogonal(const Vector<U>& other) const
{
    return std::abs(calc_angle(other) - M_PI_2) < EPS;
}

template <ContainerType T>
typename Vector<T>::iterator Vector<T>::begin() noexcept
{
    return iterator(*this);
}

template <ContainerType T>
typename Vector<T>::iterator Vector<T>::end() noexcept
{
    iterator it(*this);
    it += static_cast<std::ptrdiff_t>(container_size);
    return it;
}

template <ContainerType T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept
{
    return const_iterator(*this);
}

template <ContainerType T>
typename Vector<T>::const_iterator Vector<T>::end() const noexcept
{
    const_iterator it(*this);
    it += static_cast<std::ptrdiff_t>(container_size);
    return it;
}

template <ContainerType T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept
{
    return const_iterator(*this);
}

template <ContainerType T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept
{
    const_iterator it(*this);
    it += static_cast<std::ptrdiff_t>(container_size);
    return it;
}

template <ContainerType T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept
{
    return reverse_iterator(*this);
}

template <ContainerType T>
typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept
{
    reverse_iterator it(*this);
    it += static_cast<std::ptrdiff_t>(container_size);
    return it;
}

template <ContainerType T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const noexcept
{
    return const_reverse_iterator(*this);
}

template <ContainerType T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const noexcept
{
    const_reverse_iterator it(*this);
    it += static_cast<std::ptrdiff_t>(container_size);
    return it;
}

template <ContainerType T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const noexcept
{
    return const_reverse_iterator(*this);
}

template <ContainerType T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const noexcept
{
    const_reverse_iterator it(*this);
    it += static_cast<std::ptrdiff_t>(container_size);
    return it;
}

template <ContainerType T>
void Vector<T>::memory_allocation(BaseVector::size_type n, const char* func_name)
{
    try
    {
        container = std::shared_ptr<T[]>(new T[n]());
    }
    catch (std::bad_alloc&)
    {
        throw errMemory(__FILE__, __LINE__, func_name);
    }
}

template <ContainerType T>
template <typename U>
void Vector<T>::check_division_zero(const U& num, const char* func_name) const
{
    if (std::abs(num) < EPS)
        throw errDivisionZero(__FILE__, __LINE__, func_name);
}

template <ContainerType T>
void Vector<T>::check_arr_null(const T* arr, const char* func_name) const
{
    if (!arr)
        throw errArrNull(__FILE__, __LINE__, func_name);
}

template <ContainerType T>
void Vector<T>::check_index(BaseVector::size_type index, const char* func_name) const
{
    if (index >= container_size)
        throw errIndexOutOfRange(__FILE__, __LINE__, func_name);
}

template <ContainerType T>
void Vector<T>::check_size_equal(BaseVector::size_type size, const char* func_name) const
{
    if (container_size != size)
        throw errVectorsSizeNotEqual(__FILE__, __LINE__, func_name);
}

template <ContainerType T>
void Vector<T>::check_size_3(const char* func_name) const
{
    if (container_size != 3)
        throw errSizeNotCompatible(__FILE__, __LINE__, func_name);
}

template <PrintableContType T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector)
{
    os << "[";
    bool first = true;
    std::ranges::fold_left(vector, &os, [&first](std::ostream* out, const auto& val) 
    {
        if (!first)
            *out << ", ";
        first = false;
        *out << val;
        return out;
    });
    os << "] (" << vector.size() << ")\n";
    return os;
}