#include <cstddef>

// NVI --- Non Virtual Interface

// clang-format off

template <typename T>
struct memory_resource {
    void* allocate(size_t count, size_t align = alignof(std::max_align_t));
    void deallocate(void* ptr, size_t count, size_t align = alignof(std::max_align_t));
    bool is_equal(const memory_resource& other) const noexcept;

  protected:
    virtual void* do_allocate(size_t count, size_t align) = 0;
    // ...
};

// clang-format on
