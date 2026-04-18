#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>

// Idea source:
// https://github.com/tilir/cpp-masters/blob/master/allocators/shortalloc.hpp

// clang-format off

template <size_t StaticSize, size_t Align = alignof(std::max_align_t)>
class ArenaAlignUp {
  public:
    ArenaAlignUp() noexcept = default;
    ArenaAlignUp(const ArenaAlignUp& other) = delete;
    ArenaAlignUp& operator=(const ArenaAlignUp& other) = delete;

    // !!! In your stackallocator align is function argument, so you cannot use that approach
    void* allocate(size_t count) {
        assert(is_pointer_in_static_buf(cur_) && "allocator has outlived arena");
        const size_t kAlignedCount = align_up(count);
        if (static_buf_ + StaticSize - cur_ < kAlignedCount) {
            return operator new(kAlignedCount, std::align_val_t{Align});
        }

        void* res(cur_);
        cur_ += kAlignedCount;
        return res;
    }

    void deallocate(void* ptr, size_t count) noexcept {
        assert(is_pointer_in_static_buf(cur_) && "allocator has outlived arena");
        const size_t kAlignedCount = align_up(count);
        if (!is_pointer_in_static_buf(static_cast<std::byte*>(ptr))) {
            // Memory that ptr is pointer to was allocated with operator new.
            operator delete(ptr, kAlignedCount, std::align_val_t{Align});
        }

        // Memory is inside static_buf_, try to deallocate last allocated block
        if (static_cast<std::byte*>(ptr) + kAlignedCount == cur_) {
            cur_ = static_cast<std::byte*>(ptr);
        }
    }

  private:
    bool is_pointer_in_static_buf(std::byte* p) noexcept {
        return std::less_equal<std::byte*>()(static_buf_, p) &&
               std::less_equal<std::byte*>()(p, static_buf_ + StaticSize);
    }

    static size_t align_up(size_t count) noexcept {
        // Align == 2^x for some x
        // Align == 0...010...0
        // Align - 1 == 0...001...1
        // ~(Align - 1) == 1...110...0
        return (count + Align - 1) & ~(Align - 1); // [count, count + Align - 1]
    }

    alignas(Align) std::byte static_buf_[StaticSize];
    // cur_ points to memory obtained by static_buf_
    std::byte* cur_ = static_buf_;
};

// clang-format on

// void CompileTestArenaAlignUp() {
//     ArenaAlignUp<1'000, 16> arena;
// }
