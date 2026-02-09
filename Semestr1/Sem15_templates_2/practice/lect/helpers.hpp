#pragma once

template <class T, T Value>
struct IntegralConstant {
    using value_type = T;           // NOLINT
    using type = IntegralConstant;  // NOLINT

    static constexpr T value = Value;

    constexpr operator value_type() const noexcept {  // NOLINT
        return value;
    }

    constexpr value_type operator()() const noexcept {
        return value;
    }  // since c++14
};

////////////////////////////////////////////////////////////////////////////////

template <bool B>
using BoolConstant = IntegralConstant<bool, B>;

using TrueType = BoolConstant<true>;
using FalseType = BoolConstant<false>;

////////////////////////////////////////////////////////////////////////////////

template <class T>
struct TypeIdentity {
    using type = T;  // NOLINT
};
