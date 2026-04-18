#include <cstddef>

// TODO: memory management in base class, implementation in derived class
// + EBO

template <typename T, typename Alloc>
class Vactor {
    struct DataImpl: Alloc {
        DataImpl(T*, size_t, size_t, const Alloc& alloc): Alloc(alloc) {}
        DataImpl(const Alloc& alloc): Alloc(alloc) {}

        T* arr = nullptr;
        size_t size = 0;
        size_t capacity = 0;
    };
};
