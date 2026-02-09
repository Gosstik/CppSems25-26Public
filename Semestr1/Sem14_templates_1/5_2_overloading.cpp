#include <iostream>

template <typename T, typename U>
void Foo(T, U) {
    std::cout << 1 << '\n';
}

template <>
void Foo(int, int) {
    std::cout << 11 << '\n';
}

// CE
// template <typename U>
// void Foo<int, U>(int, U) {
//   std::cout << 12 << '\n';
// }

template <typename T>
void Foo(T, T) {
    std::cout << 2 << '\n';
}

template <>
void Foo(int, int) {
    std::cout << 22 << '\n';
}

// void Foo(int, int) {
//  std::cout << 3 << '\n';
// }

template <>
void Foo(int, double) {  //* specialization of first version
    std::cout << "Spec 1";
}

int main() {
    Foo(0, 0);  // ???
}
