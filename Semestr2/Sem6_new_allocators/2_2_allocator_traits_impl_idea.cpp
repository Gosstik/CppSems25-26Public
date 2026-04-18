#include <iostream>

// Container -> AllocTraits -> Allocator -> operator new -> malloc -> OS

// NOLINTBEGIN(readability-identifier-naming)
template <typename Alloc>
struct allocator_traits {
    template <typename U, typename... Args>
    static void construct(Alloc& alloc, U* ptr, const Args&... args) {
        if constexpr (/* Alloc has method construct*/) {
            alloc.construct(ptr, args...);
        } else {
            new (ptr) U(args...);
        }
    }
};
// NOLINTEND(readability-identifier-naming)
