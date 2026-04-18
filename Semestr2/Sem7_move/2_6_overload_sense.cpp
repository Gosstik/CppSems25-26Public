#include <iostream>
#include <vector>

// ??? When to use only v2?
// ??? When to use both?

// v1
template <typename T>
void Foo(T&) {
    // move/forward
    // copy
    std::cout << 1;
}

// v2
template <typename T>
void Foo(T&&) {
    // move/forward
    // move
    std::cout << 2;
}

int main() {
    int x = 1;
    const int y = 2;

    Foo(x);
    Foo(y);
    Foo(1);
    Foo(std::move(y));

    std::cout << '\n';
}
