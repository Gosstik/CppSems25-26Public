#include <iostream>

// Compiles since c++17

struct S {
    int a = 0;
    S() = default;
    S(const S&) = delete;
    // S(const S&) {
    //   std::cout << "HERE\n";
    // }
};

S Foo() { return {}; }

int main() {
    S s = Foo();
    std::cout << s.a << '\n';
}
