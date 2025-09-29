#include <iostream>

int main() {
    // clang-format off

    const char* str = "first, " "second, " "third, " "...";
    std::cout << str << '\n';

    str = "first, " "second, "
        "third, ""...";
    std::cout << str << '\n';

    size_t i = 3;
    std::cout << "Indexed string"[i] << '\n';
}
