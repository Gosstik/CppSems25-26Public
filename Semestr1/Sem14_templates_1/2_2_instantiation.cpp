#include <iostream>

// See multifile dir

template <typename T>
T Min(T a, T b) {
    return a < b ? a : b;
}

// Explicit instantiation
template int Min<int>(int a, int b);

// Forbid instantiation in current translation unit
extern template double Min<double>(double a, double b);

int main() {
    std::cout << Min<int>(1, 2) << std::endl;
    std::cout << Min<double>(1.0, 2.0) << std::endl;
}
