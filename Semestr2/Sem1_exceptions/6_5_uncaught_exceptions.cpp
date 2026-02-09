#include <exception>
#include <iostream>

// std::uncaught_exceptions (since c++17)
// std::uncaught_exception (removed since C++20)
// https://en.cppreference.com/w/cpp/error/uncaught_exception

struct A {
    ~A() {
        try {
            throw 3;
        } catch (...) {
            int val = std::uncaught_exceptions();
            std::cout << "catch in A: uncaught_exceptions=" << val << '\n';
        }
    }
};

struct B {
    ~B() {
        try {
            A a;
            throw 2;
        } catch (...) {
            int val = std::uncaught_exceptions();
            std::cout << "catch in B: uncaught_exceptions=" << val << '\n';
        }
    }
};

int main() {
    try {
        B b;
        throw 1;
    } catch (...) {
        int val = std::uncaught_exceptions();
        std::cout << "catch in main: uncaught_exceptions=" << val << '\n';
    }
}
