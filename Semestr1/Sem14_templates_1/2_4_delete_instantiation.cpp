#include <iostream>

template <typename T>
bool DivBy2(T val) {
    return val % 2 == 0;
}

// It is also specialization despite delete
template <>
bool DivBy2<float>(float val) = delete;

template <>
bool DivBy2<double>(double val) = delete;

////////////////////////////////////////////////////////////////////////////////

int main() {
    std::cout << DivBy2(1) << '\n';
    std::cout << DivBy2(2.0) << '\n';  // CE
}
