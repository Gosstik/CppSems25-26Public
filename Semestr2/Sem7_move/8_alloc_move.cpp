#include <utility>

template <typename T>
struct allocator {
    // usings ...

    allocator() noexcept = default;

    // allocate/deallocate, ...

    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args) {
        new (ptr) U(std::forward<Args>(args)...);
    }
};

int main() {}
