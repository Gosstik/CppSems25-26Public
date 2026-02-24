#include <format>
#include <iostream>
#include <stdexcept>

// function try block
// https://en.cppreference.com/w/cpp/language/try

void GetNonzeroWithCheck(int x) try {
    if (x > 0) {
        throw std::logic_error("x must be <= 0");
    }
    std::cout << "X=" << x << '\n';
} catch (const std::exception& err) {
    std::cout << std::format(
        "Caught in Handler try block for x={} :{}\n", x, err.what());
}

int main() {
    try {
        GetNonzeroWithCheck(1);
    } catch (...) {
        std::cout << "Caught!\n";
    }
}
