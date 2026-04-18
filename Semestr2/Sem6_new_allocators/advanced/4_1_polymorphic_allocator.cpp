#include <memory_resource>
#include <scoped_allocator>

// polimorphic_allocator:
// https://en.cppreference.com/w/cpp/memory/polymorphic_allocator.html

// polimorphic_allocator must satisfy Allocator named requirement so that it can
// be used in stl containers

template <typename T>
struct polymorphic_allocator_impl {
  public:
    // ... usings ...

    polymorphic_allocator_impl();
    polymorphic_allocator_impl(std::pmr::memory_resource* mr);
    // Shallow copy
    polymorphic_allocator_impl(const polymorphic_allocator_impl& other);
    // No asignment
    polymorphic_allocator_impl& operator=(
        const polymorphic_allocator_impl& other) = delete;

    T* allocate(size_t count);
    void deallocate(T* ptr, size_t count);

    // pocca, pocma, pocs = false
  private:
    std::pmr::memory_resource* resource_;
};

template <typename T>
struct polymorphic_allocator
    : std::scoped_allocator_adaptor<polymorphic_allocator_impl<T>> {
    // ...
};
