#include <iostream>

struct A {
    A() { std::cout << "A\n"; }
    ~A() { std::cout << "~A\n"; }
};

struct S {
    S(int x) {  // NOLINT
        std::cout << "S\n";
        if (x % 2 == 1) {
            throw std::invalid_argument("only even values are acceptable");
        }
        // 
    }
    ~S() { std::cout << "~S\n"; }

    A a;
};

int main() {
    try {
        S s(1);  // prints AS~A
    } catch (...) {
        // no ~S is called !!!
        std::cout << "caught!\n";
    }
}
