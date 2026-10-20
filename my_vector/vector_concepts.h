#pragma once

#include <concepts>
#include <type_traits>
#include <iterator>
#include <ostream>
#include <ranges>

template <typename From, typename To>
concept Convertible = std::convertible_to<From, To>;

template <typename From, typename To>
concept Assignable = requires(From from, To to)
{ 
    to = from; 
};

template <typename T>
concept Container = requires(T t)
{
    typename T::value_type;
    typename T::size_type;
    typename T::iterator;
    typename T::const_iterator;
    { t.size() } -> std::convertible_to<typename T::size_type>;
    { t.begin() } -> std::input_iterator;
    { t.end() } -> std::input_iterator;
};

template <typename U, typename T>
concept Summable = requires(T t, U u)
{
    { t + u } -> std::common_with<T>;
};

template <typename U, typename T>
concept SummableRev = requires(T t, U u)
{
    { u + t } -> std::common_with<T>;
};

template <typename U, typename T>
concept SummableEq = requires(T t, U u)
{
    { t += u } -> std::same_as<T&>;
};

template <typename C, typename T>
concept SummableContainer = Container<C> && Summable<typename C::value_type, T>;

template <typename C, typename T>
concept SummableEqContainer = Container<C> && SummableEq<typename C::value_type, T>;

template <typename U, typename T>
concept Subtractable = requires(T t, U u)
{
    { t - u } -> std::common_with<T>;
};

template <typename U, typename T>
concept SubtractableRev = requires(T t, U u)
{
    { u - t } -> std::common_with<T>;
};

template <typename U, typename T>
concept SubtractableEq = requires(T t, U u)
{
    { t -= u } -> std::same_as<T&>;
};

template <typename C, typename T>
concept SubtractableContainer = Container<C> && Subtractable<typename C::value_type, T>;

template <typename C, typename T>
concept SubtractableEqContainer = Container<C> && SubtractableEq<typename C::value_type, T>;

template <typename U, typename T>
concept Multipliable = requires(T t, U u)
{
    { t * u } -> std::common_with<T>;
};

template <typename U, typename T>
concept MultipliableRev = requires(T t, U u)
{
    { u * t } -> std::common_with<T>;
};

template <typename U, typename T>
concept MultipliableEq = requires(T t, U u)
{
    { t *= u } -> std::same_as<T&>;
};

template <typename C, typename T>
concept MultipliableContainer = Container<C> && Multipliable<typename C::value_type, T>;

template <typename C, typename T>
concept MultipliableEqContainer = Container<C> && MultipliableEq<typename C::value_type, T>;

template <typename U, typename T>
concept Divisible = requires(T t, U u)
{
    { t / u } -> std::common_with<T>;
};

template <typename U, typename T>
concept DivisibleRev = requires(T t, U u)
{
    { u / t } -> std::common_with<T>;
};

template <typename U, typename T>
concept DivisibleEq = requires(T t, U u)
{
    { t /= u } -> std::same_as<T&>;
};

template <typename C, typename T>
concept DivisibleContainer = Container<C> && Divisible<typename C::value_type, T>;

template <typename C, typename T>
concept DivisibleEqContainer = Container<C> && DivisibleEq<typename C::value_type, T>;

template <typename T>
concept ContainerType = std::copy_constructible<T> && std::move_constructible<T> && std::assignable_from<T&, T> && std::default_initializable<T>;

template <typename T>
concept Printable = requires(T t, std::ostream& os) 
{
    { os << t } -> std::same_as<std::ostream&>;
};

template <typename T>
concept PrintableContType = ContainerType<T> && Printable<T>;

template <typename U, typename T>
concept ConvertAssignable = Convertible<U, T> && Assignable<U, T>;

template <typename U, typename T>
concept Operationable = Divisible<U, T> && Multipliable<U, T> && Summable<U, T> && Subtractable<U, T> && DivisibleEq<U, T> && MultipliableEq<U, T> && SummableEq<U, T> && SubtractableEq<U, T>;

template <typename C, typename T>
concept OperationableContainer = Container<C> && Operationable<typename C::value_type, T>;

template <typename C, typename T>
concept CopyableContainer = Container<C> && Convertible<typename C::value_type, T> && Assignable<typename C::value_type, T>;

template <typename S, typename I>
concept SentinelIter = std::sentinel_for<S, I>;

template <typename Iter, typename T>
concept CompatibleIterator = std::input_iterator<Iter> && Convertible<std::iter_value_t<Iter>, T>;

template <typename R, typename T>
concept ConvertibleRange = std::ranges::input_range<R> && ConvertAssignable<std::ranges::range_value_t<R>, T>;

template <typename U>
concept ScalarType = !Container<U>;

template <typename U, typename T>
concept SummableScalar = Summable<U, T> && ScalarType<U>;

template <typename U, typename T>
concept SummableEqScalar = SummableEq<U, T> && ScalarType<U>;

template <typename U, typename T>
concept SubtractableScalar = Subtractable<U, T> && ScalarType<U>;

template <typename U, typename T>
concept SubtractableEqScalar = SubtractableEq<U, T> && ScalarType<U>;

template <typename U, typename T>
concept MultipliableScalar = Multipliable<U, T> && ScalarType<U>;

template <typename U, typename T>
concept MultipliableEqScalar = MultipliableEq<U, T> && ScalarType<U>;

template <typename U, typename T>
concept DivisibleScalar = Divisible<U, T> && ScalarType<U>;

template <typename U, typename T>
concept DivisibleEqScalar = DivisibleEq<U, T> && ScalarType<U>;

template <typename T>
concept Negatable = requires(T x) 
{ 
    x = -x; 
};
