#include <iostream>
#include <vector>

template <typename T>
void Foo(T&) {
    std::cout << 1 << '\n';
}

template <typename T>
void Foo(T&&) {
    std::cout << 2 << '\n';
}

int main() {
    std::vector<bool> vec(3);
    for (auto&& v : vec) {
        v = true;
    }
}
