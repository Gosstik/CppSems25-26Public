#include <iostream>

struct Base {  // NOLINT
    virtual void PureVirtualFunc() = 0;

    void Foo() {  // NOLINT
        std::cout << "f\n";
        PureVirtualFunc(); // ???
        // Base::PureVirtualFunc(); // ???
    }

    Base() {
        std::cout << "Base\n";
        // PureVirtualFunc(); // ???
        Foo();
    }

    virtual ~Base() = default;
};

void Base::PureVirtualFunc() { std::cout << "Base::PureVirtualFunc()\n"; }

struct Derived : Base {
    void PureVirtualFunc() override { std::cout << "Derived::PureVirtualFunc()\n"; }

    Derived() { std::cout << "Derived()\n"; };
};

int main() {
    // Derived d;
    Base& b = *new Derived();
    b.PureVirtualFunc();
}
