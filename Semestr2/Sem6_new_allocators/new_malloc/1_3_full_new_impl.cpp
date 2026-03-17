#include <cstddef>
#include <iostream>

// llvm impl:
// https://github.com/llvm/llvm-project/blob/main/libcxx/src/new.cpp#L46

// get_new_handler
// https://en.cppreference.com/w/cpp/memory/new/set_new_handler

void* operator new(size_t size) {
    std::cout << "new(size_t), size=" << size << std::endl;
    if (size == 0) {
        size = 1;
    }

    if (void* ptr = malloc(size)) {
        return ptr;
    }

    throw std::bad_alloc{};
}

void operator delete(void* ptr) noexcept {
    std::cout << "delete(void*)" << std::endl;
    std::free(ptr);
}

int main() {}
