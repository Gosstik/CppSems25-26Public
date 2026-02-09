#include <iostream>

// See https://cppinsights.io/

// Example of specialization in stl ? --- vector<bool>

template <typename T>
void Print(T) {
    std::cout << 1 << '\n';
}

template <>
// void Print<int64_t>(int64_t) {
void Print<int>(int) {
    std::cout << 2 << '\n';
}

// void Print(const int&) {
void Print(int) {
    std::cout << 3 << '\n';
}

int main() {
    int x = 1;
    Print(x);
    // Print(1.0);
}
