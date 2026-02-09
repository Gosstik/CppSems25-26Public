#include <iostream>

// override needs in case we accidentally make a mistake in method signature
// (forget const qualifier)

// 'virtual final' function --- to forbid redefinition of function

struct Base {
    virtual void Foo() const { std::cout << 1 << '\n'; }
};

struct Derived : Base {
    // virtual void Foo() { std::cout << 2 << '\n'; }  // NOLINT
    void Foo() override { std::cout << 2 << '\n'; }  // NOLINT
};

int main() {
    Derived d;
    Base& b = d;
    b.Foo(); // ???
}
