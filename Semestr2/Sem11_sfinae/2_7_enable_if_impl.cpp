#include <iostream>
#include <type_traits>

// NOLINTBEGIN(readability-identifier-naming)

// enable_if == is_same without second type

template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
    using type = T;  // NOLINT
};

template <bool B, typename T = void>
using enable_if_t = enable_if<B, T>::type;

////////////////////////////////////////////////////////////////////////////////

// Redefinition
// Name lookup shows that signatures differs only by default argument
// Substitution of default arguments occurs after name lookup

// template <typename T, typename = enable_if_t<std::is_integral_v<T>>>
// auto Foo(T val) {
//     std::cout << "integral value: " << val << '\n';
// }

// template <typename T, typename = enable_if_t<!std::is_integral_v<T>>>
// auto Foo(T val) {
//     std::cout << val << '\n';
// }

////////////////////////////////////////////////////////////////////////////////

// Solution

// Name lookup is deferred until template substitution

template <typename T, enable_if_t<std::is_integral_v<T>, bool> = true>
auto Bar(T val) {
    std::cout << "integral value: " << val << '\n';
}

template <typename T, enable_if_t<!std::is_integral_v<T>, bool> = true>
auto Bar(T val) {
    std::cout << val << '\n';
}

////////////////////////////////////////////////////////////////////////////////

// Example above:
// https://en.cppreference.com/w/cpp/types/enable_if#Notes

int main() {
    Bar(10);
    Bar("abc");
}

// NOLINTEND(readability-identifier-naming)
