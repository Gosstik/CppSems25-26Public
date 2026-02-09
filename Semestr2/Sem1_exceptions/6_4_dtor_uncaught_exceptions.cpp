#include <exception>
#include <format>
#include <iostream>
#include <string>

// Problem: dtor may be called during stack unwinding caused by other exception

struct A {
    A() = default;
    A(int a) : a(a) {}  // NOLINT

    ~A() noexcept(false) {
        std::cout << "~A() for a=" << a << '\n';

        if (a % 2 == 0) {
            int n = std::uncaught_exceptions();
            if (n > 0) {
                std::cout << std::format(
                    "uncaught_exceptions()={}, not throwing\n", n);
            } else {
                throw std::runtime_error("error with a=" + std::to_string(a));
            }

            // will cause std::terminate
            // throw std::runtime_error("error with a=" + std::to_string(a));
        }
    }

    int a;
};

void Foo() {
    A a0(0);
    A a1(1);
    A a2(2);
    A a3(3);
    A a4(4);
    A a5(5);
    A a6(6);
}

int main() {
    try {
        Foo();
    } catch (const std::exception& err) {
        std::cout << "Foo failed:" << err.what() << '\n';
    }
}
