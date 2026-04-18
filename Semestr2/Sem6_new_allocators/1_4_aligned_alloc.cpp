#include <cstdlib>
#include <cstring>
#include <iostream>

// aligned_alloc
// https://en.cppreference.com/w/cpp/memory/c/aligned_alloc

// void* aligned_alloc(size_t alignment, size_t size);
// !!! 'size' must be a multiple of 'alignment'

// malloc always align memory as alignas(std::max_align_t)
// https://en.cppreference.com/w/cpp/types/max_align_t

int main() {
    const size_t kAlignment = 64;
    const size_t kSize = 256;

    void* ptr = std::aligned_alloc(kAlignment, kSize);
    // void* ptr = std::malloc(kSize);
    if (ptr == nullptr) {
        std::cerr << "Allocation failed!" << std::endl;
        return 1;
    }

    // Verify alignment
    auto remainder = reinterpret_cast<size_t>(ptr) % kAlignment;
    std::cout << "Pointer address: " << ptr << ", remainder: " << remainder
              << std::endl;

    // !!! free the memory with std::free()
    std::free(ptr);
}
