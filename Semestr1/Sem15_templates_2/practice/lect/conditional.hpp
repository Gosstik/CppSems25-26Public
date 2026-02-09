#pragma once

#include "helpers.hpp"
#include "is_same.hpp"

template <bool B, typename T, typename F>
struct ConditionalSimple {
    using type = F;  // NOLINT
};

template <typename T, typename F>
struct ConditionalSimple<true, T, F> {
    using type = T;  // NOLINT
};

////////////////////////////////////////////////////////////////////////////////

template <bool B, typename T, typename F>
struct Conditional : TypeIdentity<F> {};

template <typename T, typename F>
struct Conditional<true, T, F> : TypeIdentity<T> {};

// since C++14
template <bool B, typename T, typename F>
using conditional_t = typename Conditional<B, T, F>::type;  // NOLINT

////////////////////////////////////////////////////////////////////////////////

void TestConditional() {
    static_assert(is_same_v<conditional_t<true, int, double>, int>);
    static_assert(is_same_v<conditional_t<false, int, double>, double>);
}
