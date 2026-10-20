#pragma once
#include <concepts>
#include <type_traits>

template <typename Type>
concept Abstract = std::is_abstract_v<Type>;

template <typename Type>
concept NotAbstract = !std::is_abstract_v<Type>;

template <typename Derived, typename Base>
concept Derivative = std::is_base_of_v<Base, Derived> && !std::is_same_v<Base, Derived> && Abstract<Base>;

template <typename Type, typename... Args>
concept Constructible = requires(Args&&... args)
{
    Type{std::forward<Args>(args)...};
};

template <typename T, typename... Allowed>
concept IsSupportedArg = (std::same_as<T, Allowed> || ...);