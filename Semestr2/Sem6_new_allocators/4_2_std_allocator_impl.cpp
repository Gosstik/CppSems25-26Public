#include <iostream>
#include <list>
#include <memory>
#include <vector>

// NOLINTBEGIN(readability-identifier-naming)
template <typename T>
struct allocator {
    // ctor, copy, operator= are default
    // operator= always return true

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    allocator() noexcept = default;

    T* allocate(size_t count) {
        std::cout << "Allocate " << count * sizeof(T) << " bytes\n";
        // return reinterpret_cast<T*>(new char[count * sizeof(T)]); // WRONG
        return static_cast<T*>(operator new(count * sizeof(T))); // !!! align
    }
    void deallocate(T* ptr, size_t count) {
        // delete[] reinterpret_cast<char*>(ptr); // WRONG
        std::cout << "Deallocate " << count * sizeof(T) << " bytes\n";
        operator delete(ptr);
    }

    // In List construct(T) will be called by NodeAlloc
    template <typename U, typename... Args>
    void construct(U* ptr, const Args&... args) {
        new (ptr) U(args...);
    }
    // template <typename... Args>
    // void construct(T* ptr, const Args&... args) {
    //   new (ptr) T(args...);
    // }

    template <typename U>
    void destroy(U* ptr) {
        ptr->~U();
    }
    // void destroy(T* ptr) {
    //   ptr->~T();
    // }

    // Rebind (for List)
    // ??? Why we cannot receive Alloc as template template parameter to
    // container

    template <typename U>
    struct rebind {
        using other = allocator<U>;
    };

    template <typename U>
    allocator(allocator<U>) {}  // NOLINT(google-explicit-constructor)
};
// NOLINTEND(readability-identifier-naming)

int main() {
    // std::list<int, allocator<int>> list;
    // list.push_back(1);
    // list.push_back(2);
    // list.push_back(3);

    std::vector<int, allocator<int>> vec;
    for (size_t i = 0; i < 30; ++i) {
        vec.push_back(i);
    }

    std::allocator<int> alloc;
    int* ptr = alloc.allocate(10);  // see implementation
}
