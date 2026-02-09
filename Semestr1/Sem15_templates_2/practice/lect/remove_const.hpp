#pragma once

#include "helpers.hpp"
#include "is_same.hpp"

template <typename T>
struct RemoveConst : TypeIdentity<T> {};

template <typename T>
struct RemoveConst<const T> : TypeIdentity<T> {};

template <typename T>
using remove_const_t = RemoveConst<T>::type;  // NOLINT

////////////////////////////////////////////////////////////////////////////////

void TestRemoveConst() {
    static_assert(is_same_v<remove_const_t<int>, int>);
    static_assert(is_same_v<remove_const_t<const int>, int>);
    // static_assert(is_same_v<remove_const_t<const int&>, int&>); // CE ???
    // static_assert(is_same_v<remove_const_t<const int*>, int*>); // CE ???
}
