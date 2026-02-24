#include <iostream>
#include <stdexcept>

// https://stackoverflow.com/questions/43609186/local-static-object-and-exception

struct A {
    A(int x) {
        std::cout << "A(" << x << ")" << std::endl;
        if (x < 1) {
            throw std::runtime_error("Ooops");
        }
        val = x;
    }

    int val;
};

void Foo(int x) {
    static A a = A(x);
    std::cout << "Foo ended, x=" << x << ", a.val=" << a.val << std::endl;
}

int main() {
    try {
        Foo(0);
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    Foo(1);  // static variable will try to initialize the second time
    Foo(0);  // no initialization of static variable
}
