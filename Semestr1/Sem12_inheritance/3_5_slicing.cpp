#include <iostream>

// Change inheritance to private?

struct Base {
    Base() = default;
    Base(const Base& other) : x(other.x) { std::cout << "Base copy!\n"; }

    int x = 1;
};

struct Derived : Base {
    Derived() = default;
    Derived(const Derived& other) : Base(), y(other.y) {
        std::cout << "Derived copy!\n";
    }

    int y = 2;
};

void Foo(Base& b) { std::cout << b.x << '\n'; }

//* Slicing
void Bar(Base b) { std::cout << b.x << '\n'; }

int main() {
    Derived d;
    Foo(d);
    Bar(d);  // OK, slicing
}
