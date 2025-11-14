#include <iostream>

struct Base {
public:
    int x = 1;

    int Foo() {
        std::cout << "Base::Foo(): " << x << '\n';
        return x;
    }
};

struct Derived : Base {
    int y = 2;

    void Bar() {
        std::cout << "Derived::Bar(): " << Foo() << '\n';
    }

    // int Foo() {
    //     std::cout << y << '\n';
    //     return y;
    // }
};

int main() {
    Base b;
    b.Foo(); // OK
    Derived d;
    d.Foo(); // OK
    d.Bar(); // OK
}
