#include <iostream>

// Out?

struct A {
    A(int x) : x(x) { std::cout << "A" << x << '\n'; }  // NOLINT
    ~A() { std::cout << "~A" << x << '\n'; }

    int x;
};

struct Base {
    Base(int x) : a0(x) { std::cout << "Base\n"; }  // NOLINT
    ~Base() { std::cout << "~Base\n"; }

    A a0;
};

struct Derived : Base {
    Derived(int y) : Base(0), a1(y) { std::cout << "Derived\n"; }  // NOLINT
    ~Derived() { std::cout << "~Derived\n"; }

    A a1;
};

int main() {
    Derived d = 1;
    std::cout << "---------\n";
}
