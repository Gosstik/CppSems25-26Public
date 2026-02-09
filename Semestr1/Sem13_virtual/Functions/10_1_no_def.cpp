#include <iostream>

struct A {
    void Foo();

    int a = 1;
};

struct B {
    virtual void Foo();

    int b = 2;
};

int main() {
    A a;
    std::cout << a.a << '\n';

    // B b; // CE (linker error)
}
