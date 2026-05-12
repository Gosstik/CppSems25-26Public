#include <concepts>
#include <iostream>
#include <type_traits>

// !!! std::same_as<T, U> subsumes std::same_as<U, T> and vice versa

namespace detail {

template <typename T, typename U>
concept SameAsHelper = std::is_same_v<T, U>;

}  // namespace detail

template <typename T, typename U>
concept SameAs = detail::SameAsHelper<T, U> && detail::SameAsHelper<U, T>;

////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
concept SameAsBad = std::is_same_v<T, U> && std::is_same_v<U, T>;

////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
    requires SameAs<T, U>
void Foo() {
    std::cout << 1 << '\n';
}

template <typename T, typename U>
    requires SameAs<U, T> && std::is_copy_constructible_v<T>
void Foo() {
    std::cout << 2 << '\n';
}

////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
    requires SameAsBad<T, U>
void Bar() {
    std::cout << 1 << '\n';
}

template <typename T, typename U>
    requires SameAsBad<U, T> && std::is_copy_constructible_v<T>
void Bar() {
    std::cout << 2 << '\n';
}

////////////////////////////////////////////////////////////////////////////////

int main() {
    Foo<int, int>();  // OK
    Bar<int, int>();  // CE
}
