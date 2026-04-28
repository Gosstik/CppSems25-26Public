#include <iostream>
#include <type_traits>
#include <utility>

// SFINAE (Substitution Failure Is Not An Error) is a C++ feature that allows
// the compiler to ignore certain template

template <
    typename T,
    typename std::enable_if_t<std::is_integral<T>::value, int*> = nullptr>
void Foo(T a) {
    std::cout << 1 << '\n';
}

template <
    typename T,
    typename std::enable_if_t<std::is_floating_point<T>::value, int*> = nullptr>
void Foo(T a) {
    std::cout << 2 << '\n';
}

// template <int = 1>
// void Foo(T a) {}

int main() {
    Foo(2.0);
    Foo(2zu);
}
