#include <iostream>
#include <new>

// How to allocate memory for std::bad_alloc in case new threw it?
// No way. It calls std::terminate if malloc fails:
// 1)
// https://github.com/llvm/llvm-project/blob/5ecc86bbcaebea5e7e480a3b2a5c4327f204bf3b/libcxxabi/src/cxa_exception.cpp#L180
// 2)
// https://github.com/llvm/llvm-project/blob/5ecc86bbcaebea5e7e480a3b2a5c4327f204bf3b/libcxxabi/src/fallback_malloc.cpp#L263

int main() {
    int* heap_addr1 = new int(1);
    try {
        throw std::bad_alloc();
    } catch (const std::bad_alloc& e1) {
        try {
            throw std::bad_alloc();
        } catch (const std::bad_alloc& e2) {
            std::cout << &e1 << '\n' << &e2 << '\n';  // different addresses
            // address is near exceptions' addresses
            std::cout << heap_addr1 << ": Heap address\n";
        }
    }
    delete heap_addr1;
}
