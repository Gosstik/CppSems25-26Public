#include <iostream>

// try godbolt with simpler example

struct A {
    A() { std::cout << "A\n"; }
    A(const A&) { std::cout << "A(copy)\n"; }
    ~A() { std::cout << "~A\n"; }
};

void Foo(bool is_thrown) {
    A a;
    if (is_thrown) {
        // throw a;  // NOLINT

        // ??? What changes
        // throw A();  // NOLINT
    }
}

int main() {
    try {
        Foo(true);
    } catch (...) {
        std::cout << "caught!\n";
    }

    std::cout << "-------------------------\n";

    try {
        Foo(true);
    } catch (const A& a) {
        std::cout << "caught!\n";
    }
}
