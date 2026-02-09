#include <iostream>

// POD --- Plain Old Data

struct A {
    int val;
};

struct B {
    // trivial default constructor does not initialize POD types
    B() = default;
    int val;
};

struct C {
    int val{};  // in-class initializer, always gives 0
};

struct Inner {
    // Inner() = default;
    Inner() { std::cout << "Inner()\n"; }
    int val;
};

struct Outer {
    // inner non-POD types always initialized
    Inner a;
    int val;
};

int main() {
    // default-initialization of POD type without user-provided constructor
    A a1;
    // UB, even if A() is commented or A() = default
    std::cout << "UB: " << a1.val << '\n';

    // value-initialization (actually zero-initialization)
    A a2 = A();
    // OK, always 0
    std::cout << "OK: " << a2.val << '\n';

    // value-initialization (actually zero-initialization)
    A a3{};
    // OK, always 0
    std::cout << "OK: " << a3.val << '\n';

    // default-initialization
    B b1;
    // UB
    std::cout << "UB: " << b1.val << '\n';

    // default-initialization
    C c1;
    // OK, always 0
    std::cout << "OK: " << c1.val << '\n';

    // default-initialization
    Outer b;
    // UB
    std::cout << "UB: " << b.a.val << '\n';
    std::cout << "UB: " << b.val << '\n';
}
