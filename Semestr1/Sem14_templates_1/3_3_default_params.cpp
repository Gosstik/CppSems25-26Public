#include <iostream>

template <typename T>
void Foo(T x = 1.0) {
    std::cout << x << '\n';
}

template <typename T = double>
void FooBetter(T x = 1.0) {
    std::cout << x << '\n';
}

struct S {
    S() = default;
    S(int) {}
};

int main() {
    Foo(1);       // OK
    Foo<int>();   // OK
    Foo();        // CE
    FooBetter();  // OK
}
