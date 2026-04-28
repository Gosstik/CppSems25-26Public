#include <iostream>

// try to compile with c++14

template <typename T>
struct VeryLongName {
    VeryLongName(T) { std::cout << 1; }
};

// Helpers before c++17
template <typename T>
VeryLongName<T> Get(T a) {
    return VeryLongName<T>(a);
}

int main() {
    VeryLongName s(5);
    auto s2 = Get(10);
}
