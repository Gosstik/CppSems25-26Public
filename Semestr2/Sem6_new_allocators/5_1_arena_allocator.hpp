#include <cstddef>
#include <memory>
#include <new>
#include <type_traits>
#include <vector>

// polymorphic_allocator:
// https://en.cppreference.com/w/cpp/memory/polymorphic_allocator.html

template <typename Tp, typename Arena>
class ArenaAllocator {
  public:
    using value_type = Tp;
    using pointer = Tp*;
    using const_pointer = const Tp*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    static constexpr bool is_always_equal = false;

    template <typename U>
    struct rebind {
        using other = ArenaAllocator<U, Arena>;
    };

    ArenaAllocator() = default;

    explicit ArenaAllocator(Arena& storage) : arena_(&storage) {}

    template <typename U>
    explicit ArenaAllocator(const ArenaAllocator<U, Arena>& other) {
        arena_ = other.arena_;
    }

    // ... assignment operators are missed

    // Alignment is not passed to allocate/deallocate
    // because it is arena template parameter.

    pointer allocate(size_type count) {
        return static_cast<pointer>(arena_->allocate(count * sizeof(Tp)));
    }

    void deallocate(pointer ptr, size_type count) {
        arena_->deallocate(ptr, count * sizeof(Tp));
    }

    // construct(...) and destroy(...) are optional

    ArenaAllocator select_on_container_copy_construction() const {
        // Create allocator on the same storage
        return ArenaAllocator(arena_);
    }

    template <typename T, size_t Size>
    friend bool operator==(
        const ArenaAllocator<T, Arena>& lhs,
        const ArenaAllocator<T, Arena>& rhs) noexcept;

    // May comment them because all are std::false_type by default
    static constexpr std::false_type propagate_on_container_copy_assignment;
    static constexpr std::false_type propagate_on_container_move_assignment;
    static constexpr std::false_type propagate_on_container_swap;

  private:
    template <typename U, typename A>
    friend class ArenaAllocator;

    Arena* arena_;
};

// void CompileTestArenaAllocator() {
//     ArenaAllocator<int, Arena> allocator;
//     std::vector<int, ArenaAllocator<int, Arena>> vec(allocator);
// }
