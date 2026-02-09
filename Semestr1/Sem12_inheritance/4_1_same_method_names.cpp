#include <iostream>

struct Base {
    int x = 1;
    void Foo() const { std::cout << x << '\n'; }
};

struct Derived : Base {
    int y = 2;
    int i;
    void Foo() const { std::cout << y << '\n'; }
};

void Tmp(Derived d) {
    d.Foo();
}

int main() {
    Derived d{};
    d.Foo();  // ???

    Base b(d);
    b.Foo();  // ???

    Base& rb(d);
    rb.Foo();  // ???

    // Tmp(b); // CE

    // Derived rd(b);
    // rd.Foo();  // ???
}
