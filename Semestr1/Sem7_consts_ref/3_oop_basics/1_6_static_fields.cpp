#include <format>
#include <iostream>

struct S {
    void Foo() {
        ++x;  // OK
        ++y;  // OK
        std::cout << std::format("Foo, x={}, y={}\n", x, y);
        // std::cout << "Foo, x=" << x << ", y=" << y << '\n'; // Same as above
    }

    static int x;
    // inline static int x = 0;
    // static const int x = 0; // !!! works even without 'inline'
    int y = 1;
};

int S::x = 0;

int main() {
    S s1;
    S s2;

    s1.Foo();
    s2.Foo();

    s1.x = 10;  // OK, but bad codestyle
    S::x = 10;  // OK

    s2.y = 20;  // OK
    // S::y = 20; // CE

    std::cout << sizeof(S) << '\n';  // ???
}
