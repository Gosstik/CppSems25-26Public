#include <iostream>

// 1. Example with const
// 2. Arguments may be omitted

// Promotions and convertions:
// https://cppreference.com/w/cpp/language/implicit_cast.html

// Integer promotion
// Floating-point promition

// Difference of promotion and convertion:
// Promotion saves value, while convertion may cause loss of precision

void Foo(int) {
    std::cout << 1 << '\n';
}

void Foo(long long) {
    std::cout << 2 << '\n';
}

int main() {
    int a;
    long b;

    Foo(a); // OK
    // Foo(b); // CE

    Foo(1); // OK
    Foo(1ll); // OK
}
