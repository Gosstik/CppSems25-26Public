#include <cstddef>
#include <cstdlib>
#include <iostream>

void* operator new(size_t n, int a, double b) {
    std::cout << n << " bytes allocated with custom new " << a << ' ' << b
              << '\n';
    return malloc(n);
}

void operator delete(void* ptr, int a, double b) noexcept {
    std::cout << "custom delete called " << a << ' ' << b << '\n';
    free(ptr);
}

int main() {
    // custom new
    // 1)
    int* p = new (1, 3.14) int(5);
    // 2)
    // void* rp = operator new (5, 2, 5.25);
    // int* p = new (rp) int(5);

    // delete p; // !!! UB if delete is not overriden

    // [there must be call to destructor if needed]
    // delete(2, 5.25) p;
    operator delete(p, 2, 5.25);
}
