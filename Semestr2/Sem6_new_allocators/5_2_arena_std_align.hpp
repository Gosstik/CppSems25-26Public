#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>

// clang-format off

// operator<() is not applicable to unrelated pointers.
// std::less() guarantees "implementation-defined strict total order over pointers":
// https://en.cppreference.com/w/cpp/language/operator_comparison.html#Pointer_total_order
// !!! NOTE: std::less "May throw implementation-defined exceptions"

// void* align(
//   std::size_t alignment,  // the desired alignment (MUST be power of 2)
//   std::size_t size,       // the size of the storage to be aligned
//   void*& ptr,             // pointer to contiguous storage (a buffer) of at least space bytes
//   std::size_t& space      // the size of the buffer in which to operate
// );

// That type of Arena is slightly worse than ArenaAlignUp
template <size_t StaticSize, size_t Align = alignof(std::max_align_t)>
class ArenaStdAlign {
  public:
    ArenaStdAlign() noexcept = default;
    ArenaStdAlign(const ArenaStdAlign& other) = delete;
    ArenaStdAlign& operator=(const ArenaStdAlign& other) = delete;

    void* allocate(size_t count) {
        assert(is_pointer_in_static_buf(cur_) && "allocator has outlived arena");
        void* aligned_cur = cur_;
        size_t space_left = static_buf_ + StaticSize - cur_;
        if (std::align(Align, count, aligned_cur, space_left) == nullptr) {
            // count does not fit in static_buf_, allocate on heap instead
            return operator new(count, std::align_val_t{Align});
        }

        // Update cur_ with the aligned pointer
        cur_ = static_cast<std::byte*>(aligned_cur);

        // Reserve memory chunk from cur_ and return it
        void* res(aligned_cur);
        cur_ += count;
        return res;
    }

    void deallocate(void* ptr, size_t count) noexcept {
        assert(is_pointer_in_static_buf(cur_) && "allocator has outlived arena");
        if (!is_pointer_in_static_buf(static_cast<std::byte*>(ptr))) {
            // Memory that ptr is pointer to was allocated with operator new.
            operator delete(ptr, count, std::align_val_t{Align});
        }

        // Memory is inside static_buf_, do nothing
    }

  private:
    // !!! Cannot use just operator<:
    // comparing unrelated pointers with relational operators is UB.
    // But std::less_equal guarantees a well-defined strict total order over all pointers.
    bool is_pointer_in_static_buf(std::byte* p) noexcept {
        return std::less_equal<std::byte*>()(static_buf_, p) &&
               std::less_equal<std::byte*>()(p, static_buf_ + StaticSize);
    }

    alignas(Align) std::byte static_buf_[StaticSize];
    // cur_ points to memory obtained by static_buf_
    std::byte* cur_ = static_buf_;
};

// clang-format on

// void CompileTestArenaStdAlign() {
//     ArenaStdAlign<1'000, 16> arena;
// }
