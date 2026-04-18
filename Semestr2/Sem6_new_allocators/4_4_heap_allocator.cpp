#include <array>
#include <cstddef>
#include <iterator>
#include <memory>
#include <new>
#include <type_traits>

class HeapStorage {
  public:
    HeapStorage() = default;
    HeapStorage(const HeapStorage& other) = delete;
    HeapStorage& operator=(const HeapStorage& other) = delete;

    template <size_t Align = alignof(std::max_align_t)>
    void* allocate(size_t count, size_t align = alignof(std::max_align_t)) {
        return operator new(count, std::align_val_t{align});
    }

    void deallocate(
        void* ptr, size_t count, size_t align = alignof(std::max_align_t)) {
        // OK, required -fsized-deallocation in clangd
        operator delete(ptr, count, std::align_val_t{align});
    }

    bool is_equal(const HeapStorage& other) const noexcept { return true; }
};

// Must be light, fast copy and assignment
template <typename Tp>
class HeapStorageAllocator {
  public:
    using value_type = Tp;
    using pointer = Tp*;
    using const_pointer = const Tp*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    static constexpr bool is_always_equal = false;

    template <typename U>
    struct rebind {
        using other = HeapStorageAllocator<U>;
    };

    HeapStorageAllocator() = default;

    explicit HeapStorageAllocator(HeapStorage& storage) : storage_(&storage) {}

    template <typename U>
    explicit HeapStorageAllocator(const HeapStorageAllocator<U>& other) {
        storage_ = other.storage_;
    }

    // TODO: implement assignment ???

    // TODO: must suport alignment
    pointer allocate(size_type count) {
        return static_cast<pointer>(
            storage_->allocate(count * sizeof(Tp), alignof(Tp)));
        // return static_cast<pointer>(operator new(
        //     count * sizeof(Tp), std::align_val_t{alignof(Tp)}
        // ));
    }

    void deallocate(pointer ptr, size_type count) {
        storage_->deallocate(ptr, count * sizeof(Tp), alignof(Tp));
        // operator delete(ptr, count * sizeof(Tp),
        // std::align_val_t{alignof(Tp)});
    }

    // construct and destroy are optional

    HeapStorageAllocator select_on_container_copy_construction() const {
        // Create allocator on the same storage
        return HeapStorageAllocator(storage_);
    }

    template <typename T, size_t Size>
    friend bool operator==(
        const HeapStorageAllocator<T>& lhs, const HeapStorageAllocator<T>& rhs) noexcept;

    static constexpr std::false_type propagate_on_container_copy_assignment;
    static constexpr std::false_type propagate_on_container_move_assignment;
    static constexpr std::false_type propagate_on_container_swap;

  private:
    template <typename U, size_t Size>
    friend class HeapAllocator;

    HeapStorage* storage_;
};
