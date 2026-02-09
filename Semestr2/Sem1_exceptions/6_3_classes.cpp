#include <exception>
#include <iostream>

// Problem: dtor may be called during stack unwinding caused by other exception
// since C++11 dtors are noexcept by default

struct A {
    A() = default;  // noexcept by default IF DTOR IS NOEXCEPT
    ~A() = default;
};

struct B {
    B() = default;
    ~B() noexcept(false) = default;
};

struct C {
    C() {}           // noexcept(false)
    ~C() = default;  // always noexcept by default
};

void Foo() {
    A a;
    throw 2;
}

int main() {
    try {
        Foo();
    } catch (const std::exception& e) {
        // won't catch primitive types (int, char, bool, ...)
    } catch (int) {
        std::cout << "caught int!\n";
    }

    A a;
    std::cout << noexcept(A());     // 1
    std::cout << noexcept(a.~A());  // 0

    std::cout << '\n';

    B b;
    std::cout << noexcept(B());     // 1 g++, 0 clang, 0 by standard
    std::cout << noexcept(b.~B());  // 1

    std::cout << '\n';

    C c;
    std::cout << noexcept(C());       // 0
    std::cout << noexcept(c.~C());    // 1
    std::cout << noexcept(C().~C());  // 0 ???

    std::cout << '\n';
}
