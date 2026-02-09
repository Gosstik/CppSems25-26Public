#include <iostream>

template <typename T>
struct S {
    template <typename U>
    int Foo();
};

template <typename T>
template <typename U>
int S<T>::Foo() {
    return 1;
}

//// CE
// template <typename T>
// template <>
// void S<T>::Foo() {
//     std::cout << 2;
// }

//// OK
template <>
template <>
int S<int>::Foo<double>() {
    return 2;
}

int main() {
    std::cout << S<double>().Foo<int>() << '\n';  // 1
    std::cout << S<int>().Foo<double>() << '\n';  // 2
}
