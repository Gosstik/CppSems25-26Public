#include <iostream>

template <typename T>
struct A {};

// Also partial specialization
template <typename T>
struct A<T&> {
    A() = delete;
};

template <typename T>
struct A<const T> {
    A() = delete;
};

int main() {
    A<const int&>
        a;  // choose A<T&>, reference has higher priority than const !!!
}
