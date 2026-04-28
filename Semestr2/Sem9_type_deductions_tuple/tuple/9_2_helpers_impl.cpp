#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

// https://en.cppreference.com/w/cpp/utility/tuple/make_tuple
// https://en.cppreference.com/w/cpp/utility/tuple/forward_as_tuple

// NOLINTBEGIN(readability-identifier-naming)

//// Incorrect: creates tuple of references in previous example
// template <typename... Ts>
// std::tuple<Ts...> make_tuple(Ts&&... args) {
//   return {std::forward<Ts>(args)...};
// }

/// Add spec for std::reference_wrapper !!!
template <typename... Ts>
std::tuple<std::decay_t<Ts>...> make_tuple(Ts&&... args) {
    return {std::forward<Ts>(args)...};
}

template <typename... Ts>
std::tuple<Ts&...> tie(Ts&... args) noexcept {
    return {args...};
}

// !!! noexcept
template <typename... Ts>
std::tuple<Ts&&...> forward_as_tuple(Ts&&... args) noexcept {
    return {std::forward<Ts>(args)...};
}

// NOLINTEND(readability-identifier-naming)

int main() { std::forward_as_tuple(1, 2); }
