#include <iostream>
#include <vector>

// SFINAE --- Substitution Failure Is Not An Error

template <typename... Args>
auto Foo(Args... args) {
    std::cout << "fallback\n";
}

template <typename Container, typename = Container::value_type>
auto Foo(Container c) {
    std::cout << 1 << '\n';
    return c[0];
}

// template <typename Container>
// auto Foo(Container c) {
//     std::cout << 1 << '\n';
//     return c[0];
// }

int main() {
    Foo(0);                          // OK, fallback
    Foo(std::vector<char>(3, 'a'));  // OK, 1
}
