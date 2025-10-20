#include <iostream>

// All escape sequences:
// https://en.cppreference.com/w/cpp/language/escape.html

int main() {
    // Escape sequences
    const char* s1 = "1:\ttext";
    const char* s10 = "10:\ttext";
    const char* s100 = "100:\ttext";

    std::cout << s1 << '\n';
    std::cout << s10 << '\n';
    std::cout << s100 << '\n';

    std::cout << "-----\n";

    const char* vs = "First text\vSecond text";
    std::cout << vs << '\n';
}
