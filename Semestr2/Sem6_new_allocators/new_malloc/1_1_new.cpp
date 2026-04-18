#include <iostream>
#include <string>
#include <vector>

// new (operator) consists of two phases:
// 1) Allocates memory (operator new)
// 2) Calls ctor (placement new)

// All versions of operator new
// https://en.cppreference.com/w/cpp/memory/new/operator_new

// What version uses vector (new or new[]) ???

// !!! Try to comment sized versions of delete and run it with ASan.
// Read [new.delete.single] chapter in standard to know the truth.

void* operator new(size_t n) {
    std::cout << n << " bytes allocated\n";
    return malloc(n);
}

// (1) Unsized delete — doesn't know how much was allocated
void operator delete(void* ptr) noexcept {
    std::cout << "delete (unsized)\n";
    std::free(ptr);
}

// (5) Sized delete — compiler tells us the size
void operator delete(void* ptr, size_t) noexcept {
    std::cout << "delete (sized)\n";
    std::free(ptr);
}

// Try to comment new[] and delete[] and disable sanitizers :)

void* operator new[](size_t n) {
    std::cout << n << "[] bytes allocated\n";
    return malloc(n);
}

// !!! Try to comment it:
// default unsised operator delete[] uses delete[](void*)
void operator delete[](void* ptr) noexcept {
    std::cout << "delete[] (unsized)\n";
    free(ptr);
}

// void operator delete[](void* ptr, size_t) noexcept {
//     std::cout << "delete[] (sized)\n";
//     free(ptr);
// }

///////////////////////////

int main() {
    {
        int* a = new int;
        delete a;

        int* arr = new int[10]{};
        delete[] arr;
    }

    // {
    //     std::vector<int> v;
    //     for (int i = 0; i < 50; ++i) {
    //         v.push_back(i);
    //     }
    // }

    //// Additional 8 bytes are used for count of dtors to call
    // {
    //     std::cout << sizeof(std::string) << '\n';  // output: 32

    //     // output in new[]: 328 = 320 + 8
    //     // std::string* ps = new std::string[10](
    //     //     "abccccccccccccccccccccccccccccccccccccccccccc",
    //     //     "abcccccccccccccccccccccc");
    //     // delete[] ps;

    //     std::string* ps1 = new std::string[1]{"abc"};  // output: 40 = 32 + 8
    //     delete[] ps1;
    // }
}
