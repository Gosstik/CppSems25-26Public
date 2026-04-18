#include <cstddef>
#include <iostream>
#include <memory_resource>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

// NOTE: new_delete_resource uses operator new(count, align)
// is contraast with std::allocator: operator new(count)

void* operator new(size_t n, std::align_val_t al) {
    std::cout << n << " bytes allocated\n";
    return malloc(n);
}

void operator delete(void* ptr, std::align_val_t al) noexcept {
    std::cout << "delete\n";
    free(ptr);
}

////////////////////////////////////////////////////////////////////////////////

constexpr size_t kBufSize = 1000 * sizeof(int);

int main() {
    alignas(int) static std::byte buf[kBufSize];
    static std::pmr::monotonic_buffer_resource default_alloc(
        buf, kBufSize, std::pmr::new_delete_resource());
    std::pmr::set_default_resource(&default_alloc);

    std::pmr::vector<int> v;  // default_alloc is not passed
    for (int i = 0; i < 500; ++i) {
        v.push_back(i);
    }
    std::cout << "v.size() = " << v.size() << '\n';
}
