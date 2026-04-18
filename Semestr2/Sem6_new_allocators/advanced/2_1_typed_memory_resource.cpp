#include <cstddef>

// memory_resource is pool of memory
// allocator is only adapter for memory (only in C++)

template <typename T>
struct typed_memory_resource {
    T* allocate(size_t count);
    void deallocate(T* ptr, size_t count);
};
