#include <iostream>
#include <vector>

// CTAD --- Class Template Argument Deduction

template <typename T>
struct A {
    A(T val) : val(val) {}  // NOLINT

    T val;
};

template <typename T>
void Foo(T) = delete;

int main() {
    {
        A ai(1);
        A ad(1.0);

        Foo(ad);  // CE, shows A template arguments
    }

    std::vector v1(2, 4);
    std::vector v2{2, 4};
}
