#include <iostream>
#include <stdexcept>

// function try block
// https://en.cppreference.com/w/cpp/language/try

int GetNonzeroWithCheck(int x) try {
    if (x > 0) {
        throw std::logic_error("x must be <= 0");
    }
    std::cout << "X=" << x << '\n';
    return x;
} catch (const std::exception& err) {
    std::cout << "Exception in Handler: " << err.what() << '\n';
}  // NOLINT

int main() {
    int x{};
    std::cin >> x;
    try {
        std::cout << GetNonzeroWithCheck(x) << '\n';
    } catch (...) {
        std::cout << "Caught!\n";
    }
}
