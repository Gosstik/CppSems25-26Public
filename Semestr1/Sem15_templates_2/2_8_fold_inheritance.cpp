#include <iostream>

template <typename... Mixins>
struct S : Mixins... {
    void PrintX() {
        ((std::cout << Mixins::x << ' '), ...);
        std::cout << '\n';
    }
};

struct A {
    int x = 1;
};

struct B {
    int x = 2;
};

struct C {
    int x = 3;
};

int main() {
    S<A, B, C> s2;
    s2.PrintX();
    S<> s0;       // OK
    s0.PrintX();  // OK
}
