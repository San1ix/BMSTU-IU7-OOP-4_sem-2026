#pragma once

#include "base_vector.h"
#include "vector_concepts.h"
#include "vector_forward_iterator.h"
#include "vector_const_forward_iterator.h"
#include "vector_reverse_iterator.h"
#include "vector_const_reverse_iterator.h"

#include <iostream>
#include <memory>
#include <initializer_list>
#include <ranges>
#include <type_traits>

template <ContainerType T>
class Vector : public BaseVector
{
public:
#pragma region Alias
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = VectorForwardIterator<T>;
    using const_iterator = VectorConstForwardIterator<T>;
    using reverse_iterator = VectorReverseIterator<T>;
    using const_reverse_iterator = VectorConstReverseIterator<T>;
#pragma endregion

#pragma region Friends
    friend class VectorForwardIterator<T>;
    friend class VectorConstForwardIterator<T>;
    friend class VectorReverseIterator<T>;
    friend class VectorConstReverseIterator<T>;
#pragma endregion

#pragma region Constructors
    Vector();

    explicit Vector(const Vector<T>& other);

    Vector(Vector<T>&& other) noexcept;
    
    template <ConvertAssignable<T> U>
    explicit Vector(const Vector<U>& other);
    
    template <CopyableContainer<T> Cont>
    explicit Vector(const Cont& other);
    
    explicit Vector(BaseVector::size_type size);
    
    template <ConvertAssignable<T> U> 
    Vector(std::initializer_list<U> arr);
    
    template <ConvertAssignable<T> U> 
    Vector(BaseVector::size_type size, const U* arr);
    
    template <CompatibleIterator<T> I, SentinelIter<I> S> 
    explicit Vector(I beg, S end);
    
    template <ConvertibleRange<T> R> 
    explicit Vector(const R& r);
    
    ~Vector() override = default;
#pragma endregion

#pragma region AssignOperators
    template <ConvertAssignable<T> U> 
    Vector<T>& operator=(const std::initializer_list<U> arr);
    
    template <CopyableContainer<T> Con> 
    Vector<T>& operator=(const Con& other);
    
    template <ConvertAssignable<T> U>
    Vector<T>& operator=(const Vector<U>& other);
    
    Vector<T>& operator=(Vector<T>&& other) noexcept;
#pragma endregion

#pragma region Sum
    template <SummableContainer<T> Con>
    Vector<std::common_type_t<T, typename Con::value_type>> operator+(const Con& other) const;
    template <SummableContainer<T> Con>
    Vector<std::common_type_t<T, typename Con::value_type>> sum(const Con& other) const;
    
    template <Summable<T> U> 
    Vector<std::common_type_t<T, U>> operator+(const Vector<U>& other) const;
    template <Summable<T> U> 
    Vector<std::common_type_t<T, U>> sum(const Vector<U>& other) const;
    
    /*
    template <SummableScalar<T> U> 
    Vector<std::common_type_t<T, U>> operator+(const U& num) const;
    template <SummableScalar<T> U> 
    Vector<std::common_type_t<T, U>> plus(const U& num) const;
    */

    template <SummableEqContainer<T> Con> 
    Vector<T>& operator+=(const Con& other);
    template <SummableEqContainer<T> Con> 
    Vector<T>& sum_eq(const Con& other);

    template <SummableEq<T> U> 
    Vector<T>& operator+=(const Vector<U>& other);
    template <SummableEq<T> U> 
    Vector<T>& sum_eq(const Vector<U>& other);

    /*
    template <SummableEqScalar<T> U> 
    Vector<T>& operator+=(const U& num);
    template <SummableEqScalar<T> U> 
    Vector<T>& plus_eq(const U& num);
    */
#pragma endregion

#pragma region Sub
    template <SubtractableContainer<T> Con> 
    Vector<std::common_type_t<T, typename Con::value_type>> operator-(const Con& other) const;
    template <SubtractableContainer<T> Con>
    Vector<std::common_type_t<T, typename Con::value_type>> sub(const Con& other) const;

    template <Subtractable<T> U> 
    Vector<std::common_type_t<T, U>> operator-(const Vector<U>& other) const;
    template <Subtractable<T> U> 
    Vector<std::common_type_t<T, U>> sub(const Vector<U>& other) const;

    /*
    template <SubtractableScalar<T> U> 
    Vector<std::common_type_t<T, U>> operator-(const U& num) const;
    template <SubtractableScalar<T> U> 
    Vector<std::common_type_t<T, U>> minus(const U& num) const;
    */

    template <SubtractableEqContainer<T> Con> 
    Vector<T>& operator-=(const Con& other);
    template <SubtractableEqContainer<T> Con> 
    Vector<T>& sub_eq(const Con& other);
    
    template <SubtractableEq<T> U> 
    Vector<T>& operator-=(const Vector<U>& other);
    template <SubtractableEq<T> U> 
    Vector<T>& sub_eq(const Vector<U>& other);
    
    /*
    template <SubtractableEqScalar<T> U>
    Vector<T>& operator-=(const U& num);
    template <SubtractableEqScalar<T> U> 
    Vector<T>& minus_eq(const U& num);
    */

    Vector<T> operator-() const 
        requires Negatable<T>;
    Vector<T> neg() const 
        requires Negatable<T>;
#pragma endregion

#pragma region Mul
    template <MultipliableContainer<T> Con> 
    Vector<std::common_type_t<T, typename Con::value_type>> operator*(const Con& other) const;
    template <MultipliableContainer<T> Con>
    Vector<std::common_type_t<T, typename Con::value_type>> mul(const Con& other) const;

    template <Multipliable<T> U>
    Vector<std::common_type_t<T, U>> operator*(const Vector<U>& other) const;
    template <Multipliable<T> U>
    Vector<std::common_type_t<T, U>> mul(const Vector<U>& other) const;

    template <MultipliableScalar<T> U>
    Vector<std::common_type_t<T, U>> operator*(const U& num) const;
    template <MultipliableScalar<T> U>
    Vector<std::common_type_t<T, U>> mul(const U& num) const;

    template <MultipliableEqContainer<T> Con>
    Vector<T>& operator*=(const Con& other);
    template <MultipliableEqContainer<T> Con>
    Vector<T>& mul_eq(const Con& other);
    
    template <MultipliableEq<T> U>
    Vector<T>& operator*=(const Vector<U>& other);
    template <MultipliableEq<T> U>
    Vector<T>& mul_eq(const Vector<U>& other);
    
    template <MultipliableEqScalar<T> U>
    Vector<T>& operator*=(const U& num);
    template <MultipliableEqScalar<T> U>
    Vector<T>& mul_eq(const U& num);
#pragma endregion

#pragma region Div
    template <DivisibleContainer<T> Con>
    Vector<std::common_type_t<T, typename Con::value_type>> operator/(const Con& other) const;
    template <DivisibleContainer<T> Con>
    Vector<std::common_type_t<T, typename Con::value_type>> div(const Con& other) const;

    template <Divisible<T> U>
    Vector<std::common_type_t<T, U>> operator/(const Vector<U>& other) const;
    template <Divisible<T> U>
    Vector<std::common_type_t<T, U>> div(const Vector<U>& other) const;

    template <DivisibleScalar<T> U> 
    Vector<std::common_type_t<T, U>> operator/(const U& num) const;
    template <DivisibleScalar<T> U>
    Vector<std::common_type_t<T, U>> div(const U& num) const;

    template <DivisibleEqContainer<T> Con>
    Vector<T>& operator/=(const Con& other);
    template <DivisibleEqContainer<T> Con>
    Vector<T>& div_eq(const Con& other);

    template <DivisibleEq<T> U>
    Vector<T>& operator/=(const Vector<U>& other);
    template <DivisibleEq<T> U>
    Vector<T>& div_eq(const Vector<U>& other);

    template <DivisibleEqScalar<T> U>
    Vector<T>& operator/=(const U& num);
    template <DivisibleEqScalar<T> U>
    Vector<T>& div_eq(const U& num);
#pragma endregion

#pragma region VectorMul
    template <OperationableContainer<T> Con>
    Vector<std::common_type_t<T, typename Con::value_type>> operator^(const Con& other) const;
    template <OperationableContainer<T> Con>
    Vector<std::common_type_t<T, typename Con::value_type>> vec_mul(const Con& other) const;

    template <Operationable<T> U>
    Vector<std::common_type_t<T, U>> operator^(const Vector<U>& other) const;
    template <Operationable<T> U>
    Vector<std::common_type_t<T, U>> vec_mul(const Vector<U>& other) const;

    template <OperationableContainer<T> Con> 
    Vector<T>& operator^=(const Con& other);
    template <OperationableContainer<T> Con>
    Vector<T>& vec_mul_eq(const Con& other);

    template <Operationable<T> U>
    Vector<T>& operator^=(const Vector<U>& other);
    template <Operationable<T> U>
    Vector<T>& vec_mul_eq(const Vector<U>& other);
#pragma endregion

#pragma region ScalarMul
    template <Operationable<T> U>
    double operator&(const Vector<U>& other) const;
    template <Operationable<T> U>
    double scalar_mul(const Vector<U>& other) const;
#pragma endregion

#pragma region ElementAccess
    reference operator[](BaseVector::size_type i);
    
    const_reference operator[](BaseVector::size_type i) const;
    
    template <ConvertAssignable<T> U> 
    Vector<T>& set_item(BaseVector::size_type i, const U& e);
    
    reference get_item(BaseVector::size_type i);
    
    const_reference get_item(BaseVector::size_type i) const;
#pragma endregion

#pragma region Math
    double len() const;
    
    Vector<double> normalization() const;
    
    [[nodiscard]] bool is_normalize() const;
    
    [[nodiscard]] bool is_zero() const;
    
    template <ConvertAssignable<T> U> 
    double calc_angle(const Vector<U>& other) const;
    
    template <ConvertAssignable<T> U>
    bool is_collinear(const Vector<U>& other) const;
    
    template <ConvertAssignable<T> U>
    bool is_orthogonal(const Vector<U>& other) const;
#pragma endregion

#pragma region Iterators
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;
#pragma endregion

protected:
#pragma region Checks
    void memory_allocation(BaseVector::size_type n, const char* fn);
    
    template <typename U> 
    void check_division_zero(const U& num, const char* fn) const;
    
    void check_arr_null(const T* arr, const char* fn) const;
    
    void check_index(BaseVector::size_type i, const char* fn) const;
    
    void check_size_equal(BaseVector::size_type s, const char* fn) const;
    
    void check_size_3(const char* fn) const;
#pragma endregion

private:
    std::shared_ptr<T[]> container;
};

#pragma region StreamOutput
template <PrintableContType T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v);
#pragma endregion

#pragma region FreeOperators
/*
template <ContainerType T, SummableScalar<T> U>
Vector<std::common_type_t<T, U>> operator+(const U& num, const Vector<T>& vector)
{
    return vector + num;
}
*/

template <ContainerType T, MultipliableScalar<T> U>
Vector<std::common_type_t<T, U>> operator*(const U& num, const Vector<T>& vector)
{
    return vector * num;
}

template <ContainerType T, SummableContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> operator+(const Con& other, const Vector<T>& vec) 
{
    return vec + other;
}

template <ContainerType T, MultipliableContainer<T> Con>
Vector<std::common_type_t<T, typename Con::value_type>> operator*(const Con& other, const Vector<T>& vec) 
{
    return vec * other;
}
#pragma endregion

#pragma region Assert
static_assert(Container<Vector<int>>);
#pragma endregion