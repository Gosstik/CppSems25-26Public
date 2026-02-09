#pragma once

#include "helpers.hpp"

template <typename T, typename U>
struct IsSameSimple : FalseType {
    static constexpr bool value = false;
};

template <typename T>
struct IsSameSimple<T, T> {
    static constexpr bool value = true;
};

////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
struct IsSame : FalseType {};

template <typename T>
struct IsSame<T, T> : TrueType {};

// since C++17
template <typename T, typename U>
const bool is_same_v = IsSame<T, U>::value;

////////////////////////////////////////////////////////////////////////////////

// Usage

template <typename T, typename U>
void Handler(T x, U y) {
    // ...
    if constexpr (is_same_v<T, U>) {
        x = y;
    }
}

void TestIsSame() {
    static_assert(is_same_v<int, int>);
    static_assert(!is_same_v<int, double>);
}
