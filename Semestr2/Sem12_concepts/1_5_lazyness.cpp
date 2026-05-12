#include <iostream>
#include <stdexcept>

template <int V>
int a;

constexpr int CeIfAbove9(int n) {
    if (n > 9) {
        throw std::runtime_error("err");
    }
    return n;
}

template <int N>
constexpr bool CeIfAbove9V = CeIfAbove9(N) < 100;

/// 1
template <int X>
constexpr bool IsGoodV = X >= 10 || CeIfAbove9(X);

/// 2
// template <int X>
// constexpr bool IsGoodV = CeIfAbove9(X) || X >= 10;

/// 1
template <int X>
    requires IsGoodV<X>
void Foo() {
    std::cout << "X = " << X << '\n';
}

/// 2
// template <int X>
// requires requires {
//     IsGoodV<X>;
// }
// void Foo() {
//     std::cout << "X = " << X << '\n';
// }

/// 3
// template <int X>
// requires (X > 10) || CeIfAbove9V<X>
// void Foo() {
//     std::cout << "X = " << X << '\n';
// }

/// 4
// template <int X>
// requires (X > 10) || a<X>
// void Foo() {
//     std::cout << "X = " << X << '\n';
// }

template <int X>
void Foo() {
    std::cout << "Fallback!\n";
}

int main() {
    // std::cout << IsGoodV<10> << '\n';
    Foo<50>();
}
