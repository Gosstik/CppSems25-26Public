#include <iostream>

// template <typename T, typename U>
// struct S {};

// template <typename U>
// struct S<int, U> {};

template <typename T, typename U>
void Foo(T x, U v) {
    std::cout << x << '\n';
}

template <>
void Foo<int, double>(int a, double u) {
    std::cout << 'a';
}

void Foo(int) { std::cout << 1 << '\n'; }

int main() {
    unsigned int x = 0;
    Foo(x);
}
