#include <iostream>
#include <stdexcept>

// How to free memory ??? --- use smart pointers

struct A {
    A(bool is_thrown) {  // NOLINT
        std::cout << "A\n";
        if (is_thrown) {
            throw std::logic_error("exception in A\n");
        }
    }

    ~A() { std::cout << "~A\n"; }
};

struct S {
    S() : p(new int(1)), a(true) { std::cout << "S\n"; }

    ~S() {
        std::cout << "~S";
        Clear();
    }

    void Clear() const {
        std::cout << "Clear\n";
        delete p;
    }

    // Try to change their relative position
    int* p;
    A a;
};

int main() {
    try {
        S s;
    } catch (...) {
        std::cout << "caught!\n";
    }
}
