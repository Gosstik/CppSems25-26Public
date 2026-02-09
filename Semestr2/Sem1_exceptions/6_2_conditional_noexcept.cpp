#include <iostream>

template <typename T>
void Foo(T x) noexcept(sizeof(T) < 8) {
    if (sizeof(T) >= 8) {
        throw x;
    }
    std::cout << x << '\n';
}

template <typename T>
void Bar(T a) noexcept(a == 0) {}  // CE --- not compile time condition

template <typename T>
void Baz(T a) noexcept(noexcept(a == 0)) {}  // OK, check operator==(T, int)

template <typename T>
void FooWrapper(T a) noexcept(noexcept(Foo(a))) {}

int main() {
    std::cout << noexcept(Foo(1));     // 1
    std::cout << noexcept(Foo(1ull));  // 0

    std::cout << '\n';

    // std::cout << noexcept(Bar(1)) << '\n';  // CE

    std::cout << noexcept(Baz(0));  // 1
    std::cout << noexcept(Baz(1));  // 1 !!!

    std::cout << '\n';

    std::cout << noexcept(FooWrapper(1));     // 1
    std::cout << noexcept(FooWrapper(1ull));  // 0

    std::cout << '\n';
}
