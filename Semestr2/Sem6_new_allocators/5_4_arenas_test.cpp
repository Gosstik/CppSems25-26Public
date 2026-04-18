#include <iostream>
#include <list>
#include <vector>

#include "5_1_arena_allocator.hpp"
#include "5_2_arena_std_align.hpp"
#include "5_3_arena_align_up.hpp"

////////////////////////////////////////////////////////////////////////////////

void* operator new(size_t n) {
    std::cout << n << " bytes allocated\n";
    return malloc(n);
}

void operator delete(void* ptr, size_t) noexcept {
    std::cout << "delete\n";
    free(ptr);
}

void* operator new[](size_t n) {
    std::cout << n << "[] bytes allocated\n";
    return malloc(n);
}

void operator delete[](void* ptr, size_t) noexcept {
    std::cout << "delete[]\n";
    free(ptr);
}

////////////////////////////////////////////////////////////////////////////////

static const int kArenaSize = 100;

void TestArenaStdAlign() {
    std::cout << "Start std_align test" << std::endl;
    {
        std::cout << "vector test" << std::endl;
        ArenaStdAlign<kArenaSize> arena;
        ArenaAllocator<int, ArenaStdAlign<kArenaSize>> alloc(arena);
        std::vector<int, ArenaAllocator<int, ArenaStdAlign<kArenaSize>>> c(
            alloc);
        for (int i = 0; i < 10; ++i) {
            c.push_back(i);
        }
    }

    {
        std::cout << "list test" << std::endl;
        ArenaStdAlign<kArenaSize> arena;
        ArenaAllocator<int, ArenaStdAlign<kArenaSize>> alloc(arena);
        std::list<int, ArenaAllocator<int, ArenaStdAlign<kArenaSize>>> c(alloc);
        for (int i = 0; i < 10; ++i) {
            c.push_back(i);
        }
    }
    std::cout << "Finish std_align test" << std::endl;
}

void TestArenaAlignUp() {
    std::cout << "Start align_up test" << std::endl;
    {
        std::cout << "vector test" << std::endl;
        ArenaAlignUp<kArenaSize> arena;
        ArenaAllocator<int, ArenaAlignUp<kArenaSize>> alloc(arena);
        std::vector<int, ArenaAllocator<int, ArenaAlignUp<kArenaSize>>> c(
            alloc);
        for (int i = 0; i < 10; ++i) {
            c.push_back(i);
        }
    }

    {
        std::cout << "list test" << std::endl;
        ArenaAlignUp<kArenaSize> arena;
        ArenaAllocator<int, ArenaAlignUp<kArenaSize>> alloc(arena);
        std::list<int, ArenaAllocator<int, ArenaAlignUp<kArenaSize>>> c(alloc);
        for (int i = 0; i < 10; ++i) {
            c.push_back(i);
        }
    }
    std::cout << "Finish align_up test" << std::endl;
}

int main() {
    TestArenaStdAlign();
    TestArenaAlignUp();
}
