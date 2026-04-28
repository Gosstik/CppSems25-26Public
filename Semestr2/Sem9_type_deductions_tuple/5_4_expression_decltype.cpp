#include <iostream>

//// decltype distinguishes between categories of values:
// prvalue -> T (decltype(x + 0))
// lvalue expr -> T& (decltype((x)))
// xvalue -> T&& (decltype(std::move(x)))

template <typename T>
void Debug() = delete;

int main() {
    {
        // decltype(expression)
        int x = 0;
        decltype(++x) u1 = x;  // unevaluated context
        // decltype(x++) u2 = x;
        ++u1;
        std::cout << x << u1 << '\n';  //* 11
    }

    {
        int x = 1;
        const decltype(throw 1)* px = &x;  //* const void*

        // Debug<decltype(px)>();
    }

    {
        int x = 1;
        decltype((x)) y = x;  // int&
        ++y;
        std::cout << x << y << '\n';  //* 22
    }
}
