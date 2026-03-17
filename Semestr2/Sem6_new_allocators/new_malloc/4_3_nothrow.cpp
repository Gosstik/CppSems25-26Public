#include <iostream>
#include <new>

// https://en.cppreference.com/w/cpp/memory/new/nothrow

int main() {
    try {
        while (true) {
            new int[100000000ul];  // throwing overload
        }
    } catch (const std::bad_alloc& e) {
        std::cout << e.what() << '\n';
    }

    while (true) {
        int* p = new (std::nothrow) int[100000000ul];  // non-throwing overload
        if (p == nullptr) {
            std::cout << "Allocation returned nullptr\n";
            break;
        }
        // operator delete(p, std::nothrow);
    }
}
