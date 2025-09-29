#include <cstddef>  // std::nullptr_t
#include <iostream>

int main() {
    // nullptr, NULL
    // nullptr may be assigned to any pointer
    // type: std::nullptr_t
    // in C only since C23, earlier: NULL (macros)

    int* p1;
    std::cout << p1 << '\n'; // Unspecified

    int* p2 = nullptr;
    std::cout << p2 << '\n';

    int* p3 = NULL;
    std::cout << p3 << '\n';

    std::nullptr_t nptr = nullptr;
}
