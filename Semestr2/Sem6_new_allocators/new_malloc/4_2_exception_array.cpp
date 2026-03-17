#include <cstdlib>
#include <iostream>

void* operator new[](size_t n) {
    std::cout << n << "[] bytes allocated\n";
    return malloc(n);
}

void operator delete[](void* ptr) noexcept {
    std::cout << "delete[]\n";
    free(ptr);
}

struct A {
    A(int a) {
        std::cout << "A(int): " << count << '\n';
    }

    A(): A(count){
        std::cout << "A(): " << count << '\n';
        if (count == 3) {
            --count;
            throw 1;
        }
        ++count;
    }

    ~A() {
        std::cout << "~A(): " << count << '\n';
        --count;
    }

    inline static int count = 0;
};

int main() {
    try {
        A* arr = new A[5];  // compiler must call dtors and deallocate
    } catch (...) {
        std::cout << "caught!\n";
    }
}
