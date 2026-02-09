#include <iostream>

template <typename T>
void Foo(T&) {
    std::cout << 1;
}

template <typename T>
void Foo(T) {
    std::cout << 2;
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
void Bar(const T&) {
    std::cout << 1;
}

template <typename T>
void Bar(T&) {
    std::cout << 2;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
    int x = 0;
    int& y = x;

    Foo(x);  // CE
    Foo(1);  // OK

    Bar(x);  // OK
}
