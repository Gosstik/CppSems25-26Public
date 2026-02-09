#include <iostream>

// clang++ -std=c++20 -fsanitize=address,undefined -Wall -Wextra -pedantic

// https://en.cppreference.com/w/cpp/language/reference_initialization#Lifetime_of_a_temporary
// https://eel.is/c++draft/intro.execution#def:full-expression

const int& Foo(const int& x) { return x; }

int main() {
    int x = Foo(5);
    std::cout << x << '\n';
}
