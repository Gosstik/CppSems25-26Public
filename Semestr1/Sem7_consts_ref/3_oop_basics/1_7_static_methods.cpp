#include <iostream>

struct S {
    void Foo() {
        ++x;  // OK
        ++y;  // OK
        std::cout << "Foo, x=" << x << '\n';
    }

    static void StaticFoo() {
        ++x;  // OK
        // ++y; // CE
        std::cout << "StaticFoo, x=" << x << '\n';
    }

    inline static int x = 0;
    int y = 1;
};

int main() {
    S s1;
    S s2;

    s1.Foo();
    s2.Foo();
    // S::Foo(); // CE

    s1.StaticFoo();  // OK, but bad codestyle
    s2.StaticFoo();  // OK, but bad codestyle
    S::StaticFoo();  // OK
}
