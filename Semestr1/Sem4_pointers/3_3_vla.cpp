#include <iostream>

// VLA - Variable Length Array (DO NOT USE IT !!!)
// OK in C

int main() {
    size_t n = 5;
    size_t a[n];
    for (size_t i = 0; i < sizeof(n); ++i) {
        a[i] = i;
    }
    for (size_t i = 0; i < sizeof(n); ++i) {
        std::cout << a[i];
    }
}
