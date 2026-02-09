#include <iostream>

struct Base {
public:
    int x = 1;

    int PureVirtualFunc() {
        std::cout << "Base::Foo(): " << x << '\n';
        return x;
    }
};

struct Derived : Base {
    int y = 2;

    void Bar() {
        std::cout << "Derived::Bar(): " << PureVirtualFunc() << '\n';
    }

    // int Foo() {
    //     std::cout << y << '\n';
    //     return y;
    // }
};

int main() {
    Base b;
    b.PureVirtualFunc(); // OK
    Derived d;
    d.PureVirtualFunc(); // OK
    d.Bar(); // OK
}
