#include <iostream>

// https://en.cppreference.com/w/cpp/language/overload_resolution#Ranking_of_implicit_conversion_sequences
// https://en.cppreference.com/w/cpp/language/implicit_conversion#Qualification_conversions

// 1. Exact match
// 2. Promotion
// 3. Conversion

// int& -> const int& --- qualification conversion

// void Foo(int x) { std::cout << 1 << '\n'; }
void Foo(int& x) { std::cout << 2 << '\n'; }
void Foo(const int& x) { std::cout << 3 << '\n'; }

int main() {
    int x = 0;
    int& y = x;
    const int& z = x;

    Foo(x);  // ???
    Foo(y);  // ???
    Foo(z);  // ???
    Foo(1);  // ???
}
