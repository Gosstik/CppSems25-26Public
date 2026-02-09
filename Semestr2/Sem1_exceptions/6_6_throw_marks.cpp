#include <iostream>
#include <stdexcept>

// Dynamic exception specification (deprecated in c++11, removed in C++17)
// https://en.cppreference.com/w/cpp/language/except_spec

void Foo() throw(std::runtime_error, std::logic_error) {  // NOLINT
    // throw std::runtime_error("runtime");
    // throw std::logic_error("logic");
    throw std::length_error("length");  // causes std::terminate --- not listed
}

void Bar() throw() {                      // NOLINT // throw() == noexcept
    throw std::runtime_error("runtime");  // std::terminate
}

int main() {
    try {
        // Foo();
        Bar();
    } catch (...) {
        std::cout << "caught!\n";
    }
}
