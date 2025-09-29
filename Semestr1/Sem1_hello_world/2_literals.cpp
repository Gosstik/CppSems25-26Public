#include <iostream>

int main() {
    std::cout << 1000000 << ' ' << 1'000'000 << '\n';
    std::cout << 2l << ' ' << 3ull << '\n';
    std::cout << 24.5 << ' ' << 1.0f << '\n';
    std::cout << 0b101 << '\n';  // ???
    std::cout << 010 << '\n';    // ???
    std::cout << 0xff << '\n';   // ???
}
