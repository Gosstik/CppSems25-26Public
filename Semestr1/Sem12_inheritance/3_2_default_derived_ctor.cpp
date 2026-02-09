#include <iostream>

struct Base {
    int x1;
    explicit Base(int i) : x1(i) {}
};

struct Derived : Base {
    int y;
    void Foo() const { std::cout << y << '\n'; }

    // Derived() = default;
    // Derived(const Derived& d) {}
    // using Base::Base;
    // explicit Derived(Base& b) : Base(b) {}
};

int main() {
    // Derived d;

    Base b(1);
    Derived d(b);                          //* CE
    Derived dd(static_cast<Derived&>(b));  //* Fix CE
}
