#include <iostream>

template <typename T>
void Print(T val) {
    std::cout << val << '\n';
}

template <>
void Print<int>(int val) {
    std::cout << "int version\n";
    std::cout << val << '\n';
}

void Foo() { Print(1); }

// Implicit instantiation of Print<double>
void Bar() { Print(1.0); }

// Error (must be placed before implicit instantiation)
template <>
void Print<double>(double val) {
    std::cout << "double version\n";
    std::cout << val << '\n';
}

int main() {}
