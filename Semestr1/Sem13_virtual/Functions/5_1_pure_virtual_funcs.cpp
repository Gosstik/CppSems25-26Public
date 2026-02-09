#include <iostream>

// Base --- Abstract Class (has at least 1 pure virtual function)
// !!! All pure virtual functions must be defined in successors
// !!! otherwise derived class is abstract

struct Base {  // NOLINT
    virtual void PureVirtualFunc() = 0;
};

void Base::PureVirtualFunc() { std::cout << "Base::Foo()\n"; }

struct Derived : Base {
    void PureVirtualFunc() override { std::cout << "Derived::Foo()\n"; }
};

int main() {
    // Base b;  // CE
    Derived d;
    Base& rb = d;  // OK

    rb.PureVirtualFunc();
    rb.Base::PureVirtualFunc();  // OK, devirtualization
}
