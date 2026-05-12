#include <iostream>
#include <type_traits>

template <typename T>
void Foo() {
    std::cout << 1 << '\n';
}

template <typename T>
    requires std::is_reference_v<T>
void Foo() {
    std::cout << 2 << '\n';
}

int main() {
    Foo<int>();
    Foo<int&>();
    Foo<const int&>();
}
