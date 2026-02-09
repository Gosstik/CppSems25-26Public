#include <iostream>

// Try to comment Foo() in Derived

struct Base {
    void Foo() {  // NOLINT
        std::cout << 1 << '\n';
    }

    int x;
};

struct Derived : Base {
    void Foo() {  // NOLINT
        std::cout << 2 << '\n';
    }

    int x;

  private:
    using Base::Foo;  // ???
    using Base::x;    // ???
};

int main() {
    Derived d{};
    d.Base::Foo();
    d.Foo();  // ???
}
