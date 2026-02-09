#include <iostream>

struct Base {
    Base(int x) : x(x) { std::cout << "Base1\n"; }  // NOLINT
    Base(int x, int y) : x(x + y) { std::cout << "Base2\n"; }
    Base(int x, int y, int z) : x(x + y + z) { std::cout << "Base3\n"; }

    Base(const Base& other) : x(other.x) { std::cout << "Copy\n"; }

    int x;
};

// Try to comment both ctors !!!

struct Derived : Base {
    Derived(int y) : Base(y), y(y) {}  // NOLINT

    using Base::Base;
    // cannot use Base copy ctor !!!

    int y = 0;
};

int main() {
    Derived d = 1;
    std::cout << '\n';

    Derived d2 = d;             // NOLINT
    std::cout << d2.y << '\n';  // ???

    Base b(1);
    Derived d3(b);  // CE
}
