#include <iostream>

struct Base {
    virtual void Foo(int x = 1) { std::cout << x << 1 << '\n'; }  // NOLINT
};

struct Derived : Base {
    void Foo(int x = 2) { std::cout << x << 2 << '\n'; }  // NOLINT
};

int main() {
    Derived d;
    Base& b = d;
    b.Foo();
}
