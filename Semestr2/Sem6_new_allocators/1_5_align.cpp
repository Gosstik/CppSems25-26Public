#include <format>
#include <iostream>
#include <memory>

// std::align
// https://en.cppreference.com/w/cpp/memory/align

// void* align(
//     std::size_t alignment,
//     std::size_t size,
//     void*& ptr, // !!! note *&
//     std::size_t& space
// );

int main() {
    // Allocate a raw buffer
    char buffer[256]{};

    const size_t kOffset = 1;
    void* ptr = buffer + kOffset;
    size_t space = sizeof(buffer) - kOffset;

    std::cout << "Before: ptr=" << ptr << ", space=" << space << "\n";

    // Align to 16-byte boundary for an object of size 32
    void* aligned_buf = std::align(16, 32, ptr, space);

    if (aligned_buf == nullptr) {
        std::cout << "Failed to align\n";
        return 1;
    }

    std::cout << std::format(
        "After: ptr={}, space={}, aligned_addr={}, align_remedy={}\n",
        ptr,
        space,
        aligned_buf,
        reinterpret_cast<size_t>(aligned_buf) % 16);
}
