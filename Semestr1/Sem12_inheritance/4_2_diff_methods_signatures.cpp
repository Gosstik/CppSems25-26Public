#include <iostream>

struct Base {
    // protected:
    int x = 1;
    void Foo(int) {  // NOLINT
        std::cout << 1 << '\n';
    }
};

struct Derived : Base {
    int y = 2;
    // private:

    // void Foo(float) { std::cout << 3 << '\n'; }

    void Foo() {  // NOLINT
        std::cout << 2 << '\n';
    }

    // private:
    using Base::Foo;
};

int main() {
    Derived d{};
    d.Foo(2);
    d.Base::Foo(1);

    {
        Derived d;
        d.Foo(0.0);        //* CE if 1) no using 2) using is private 3) exists
                           // Foo(float)
        d.Base::Foo(0.0);  //* OK
    }
}
