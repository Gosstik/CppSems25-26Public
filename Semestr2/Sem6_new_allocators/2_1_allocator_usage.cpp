#include <iostream>
#include <memory>
#include <new>
#include <string>
#include <vector>

struct A {
    int a = 2;
    double d = 3.14;
};

int main() {
    {
        // new-delete example

        A* a = new A(2, 3.14);

        // ... some stuff

        delete a;
    }

    {
        // Verbose new-delete example

        void* p = operator new(sizeof(A), std::align_val_t{alignof(A)});
        A* a = new (p) A(2, 3.14);  // !!! note - placement new returns pointer

        // ... some stuff

        a->~A();
        operator delete(a);
    }

    // void construct(pointer p, const T& t) { new(p) T(t); }
    // void destroy(pointer p) { p->~T(); }

    {
        // Allocator example

        std::allocator<A> alloc;
        A* a = alloc.allocate(sizeof(A));
        alloc.construct(a, 2, 3.14);  // (until C++20)

        // ... some stuff

        alloc.destroy(a);  // (until C++20)
        alloc.deallocate(a, sizeof(A));
    }

    {
        // With allocator_traits

        std::allocator<A> alloc;
        using AllocTraits = std::allocator_traits<std::allocator<A>>;

        A* a = AllocTraits::allocate(alloc, sizeof(A));
        // !!! note - construct returns void
        AllocTraits::construct(alloc, a, 2, 3.14);

        // .. some stuff

        AllocTraits::destroy(alloc, a);
        AllocTraits::deallocate(alloc, a, sizeof(A));
    }
}
