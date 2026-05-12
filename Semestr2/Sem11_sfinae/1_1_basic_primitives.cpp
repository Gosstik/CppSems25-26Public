#include <iostream>
#include <type_traits>
#include <vector>

// NOLINTBEGIN(readability-identifier-naming)

// TODO

// type_identity<T>

template <typename T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    operator value_type() const { return value; }
};

// std::bool_constant<Bool>, std::true_type, std::false_type
// is_lvalue_reference
// is_same

//// Wrong implementation. Correct impl must be lazy (short-circuiting)
template <typename... Types>
struct conjunction {  // NOLINT(readability-identifier-naming)
    static constexpr bool value = (... && Types::value);
};

// disjunction
// negation

//// What means compilation error: expected primary-expression ???
// Compiler expected expression, but get type or something else. Occurs when
// instead of _v we by mistake use meta class.

// NOLINTEND(readability-identifier-naming)

////////////////////////////////////////////////////////////////////////////////

int main() {
    // TODO
}
