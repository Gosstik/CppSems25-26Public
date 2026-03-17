#include <iostream>
#include <string>
#include <vector>

// new (operator) consists of two phases:
// 1) Allocates memory (operator new)
// 2) Calls ctor (placement new)

// All versions of operator new
// https://en.cppreference.com/w/cpp/memory/new/operator_new

// What version uses vector (new or new[]) ???

void* operator new(size_t n) {
    std::cout << n << " bytes allocated\n";
    return malloc(n);
}

void operator delete(void* ptr, size_t n) noexcept {
    std::cout << "delete\n";
    std::free(ptr);
}

// Try to comment new[] and delete[] and disable sanitizers :)

void* operator new[](size_t n) {
    std::cout << n << "[] bytes allocated\n";
    return malloc(n);
}

void operator delete[](void* ptr, size_t) noexcept {
    std::cout << "delete[]\n";
    free(ptr);
}

///////////////////////////

int main() {
    // {
    //     int* a = new int;
    //     delete a;

    //     int* arr = new int[10]{};
    //     delete[] arr;
    // }

    // {
    //     std::vector<int> v;
    //     for (int i = 0; i < 50; ++i) {
    //         v.push_back(i);
    //     }
    // }

    //// Additional 8 bytes are used for count of dtors to call
    {
        std::cout << sizeof(std::string) << '\n';  // output: 32

        // output in new[]: 328 = 320 + 8
        // std::string* ps = new std::string[10](
        //     "abccccccccccccccccccccccccccccccccccccccccccc",
        //     "abcccccccccccccccccccccc");
        // delete[] ps;

        std::string* ps1 = new std::string[1]{"abc"};  // output: 40 = 32 + 8
        delete[] ps1;
    }
}
