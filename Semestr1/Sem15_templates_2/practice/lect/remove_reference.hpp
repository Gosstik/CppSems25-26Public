#pragma once

#include "helpers.hpp"
#include "is_same.hpp"

template <typename T>
struct RemoveReference : TypeIdentity<T> {};

template <typename T>
struct RemoveReference<T&> : TypeIdentity<T> {};

template <typename T>
using remove_reference_t = RemoveReference<T>::type;  // NOLINT

////////////////////////////////////////////////////////////////////////////////

void TestRemoveReference() {
    static_assert(is_same_v<remove_reference_t<int>, int>);
    static_assert(is_same_v<remove_reference_t<int&>, int>);
    static_assert(is_same_v<remove_reference_t<const int&>, const int>);
    static_assert(is_same_v<remove_reference_t<int*&>, int*>);
}
