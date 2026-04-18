#include <cstddef>

template <typename T>
struct memory_resource {
    /* virtual */ void* allocate(
        size_t count, size_t align = alignof(std::max_align_t));
    /* virtual */ void deallocate(
        void* ptr, size_t count, size_t align = alignof(std::max_align_t));
    /* virtual */ bool is_equal(const memory_resource& other) const noexcept;
};
