#include <memory>
#include <list>

//// Named requirements
// Allocator:
// https://en.cppreference.com/w/cpp/named_req/Allocator
// AllocatorAwareContainer:
// https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer

//// Member types
// https://en.cppreference.com/w/cpp/memory/allocator_traits

// select_on_container_copy_construction() // returns new or copy (default)
// is_always_equal
// propagate_on_container_copy_assignment::value (meta function)

// Abbreviations
// propagate_on_container_copy_assignment = pocca

// !!! BASIC EXCEPTION GUARANTEE IN ASSIGNMENTS
// Rolling back is expensive/impractical.
// So only basic exception guarantee is provided.

template <typename Alloc>
class Container {
    // ... some stuff ...

    Container& operator=(const Container& other) {
        using AllocTraits = std::allocator_traits<Alloc>;
        using pocca = AllocTraits::propagate_on_container_copy_assignment;
        using iae = AllocTraits::is_always_equal;

        if (this == &other) {
            return *this;
        }
        if (pocca::value) {
            if (iae::value || alloc_ == other.alloc_) {
                // alloc_ = other.alloc()
                // inplace element-wise reassignment of impl_
                return;
            }
            // dealloc_clear() // !!! HERE WE LOOSE STRONG EXCEPTION GUARANTEE
            // alloc_ = other.alloc()
            // impl_ = copy(other.impl_);
        } else {
            // inplace element-wise reassignment of impl_
        }
    }

    // ??? Why not to implement copy with a1 != a2 like that?
    // List tmp(other);
    // clear();
    // swap(tmp);
    // !!! swap causes UB if a1 != a2 and propagate_on_container_swap == false

    Container& operator=(Container&& other) {
        using AllocTraits = std::allocator_traits<Alloc>;
        using pocma = AllocTraits::propagate_on_container_move_assignment;
        using iae = AllocTraits::is_always_equal;

        if (this == &other) {
            return *this;
        }
        if (pocma::value) {
            if (iae::value || alloc_ == other.alloc_) {
                // alloc_ = std::move(other.alloc())
                // impl_ = move(other.impl_);
                return;
            }
            // clear()
            // alloc_ = std::move(other.alloc())
            // impl_ = move(other.impl_);
        } else if (iae::value || alloc_ == other.alloc_) {
            // clear()
            // impl_ = move(other.impl_)
        } else {
            //// Allocators are not equal and must not be propagated
            // inplace element-wise reassignment of impl_
        }
    }

  private:
    // Impl impl_;
    Alloc alloc_;
};

int main() {
    std::list<int> l1;
    std::list<int> l2;
    l1 = l2; // Check impl
    l1.swap(l2);
}
