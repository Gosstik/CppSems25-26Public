#include <iostream>

template <typename... Args>
int SumTrailing(Args... args, int last) {
    return (args + ... + last);
}

int main() {
    std::cout << SumTrailing(1, 2, 3);            // CE
    std::cout << SumTrailing<int, int>(1, 2, 3);  // OK
}
