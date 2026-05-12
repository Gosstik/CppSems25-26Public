#include <cstddef>
#include <iostream>
#include <memory>
#include <memory_resource>
#include <string>

// TODO: fix CE and add logging

class PolymorphicAllocatorDelete {
  public:
    explicit PolymorphicAllocatorDelete(
        std::pmr::polymorphic_allocator<std::byte> alloc)
        : alloc_(alloc) {}

    template <typename T>
    void operator()(T* ptr) {
        alloc_.destroy(ptr);  // NOLINT
        alloc_.deallocate(reinterpret_cast<std::byte*>(ptr), sizeof(T));
    }

  private:
    std::pmr::polymorphic_allocator<std::byte> alloc_;
};

template <typename T>
class PmrUniquePtr {
  public:
    PmrUniquePtr(std::pmr::polymorphic_allocator<std::byte> alloc)
        : ptr_(nullptr, alloc) {
        T* ptr = alloc.allocate(sizeof(T));
        // T has no args in constructor
        alloc.construct(ptr);
        ptr_.reset(ptr);
    }

  private:
    std::unique_ptr<T, PolymorphicAllocatorDelete> ptr_;
};

class MyType {
  public:
    MyType() { std::cout << data_ << std::endl; }

  private:
    std::pmr::string data_{"Hello"};
};

int main() {
    std::pmr::vector<PmrUniquePtr<MyType>> vec;
    vec.emplace_back();
    vec.emplace_back();
}
