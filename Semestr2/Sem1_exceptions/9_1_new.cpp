// Why exceptions cannot be placed on stack? --- stack unwinding

// Memory for exception is allocated on heap but not always with malloc.
// It uses __cxa_allocate_exception:
// https://github.com/llvm/llvm-project/blob/5ecc86bbcaebea5e7e480a3b2a5c4327f204bf3b/libcxxabi/src/cxa_exception.cpp#L183

// __aligned_malloc_with_fallback
// https://github.com/llvm/llvm-project/blob/5ecc86bbcaebea5e7e480a3b2a5c4327f204bf3b/libcxxabi/src/fallback_malloc.cpp#L258

// Path:
// /usr/include/c++/13/bits/cxxabi_init_exception.h : line 63

// Linux in most cases uses simple malloc in __cxa_allocate_exception.

// Linux overcommiting:
// https://stackoverflow.com/questions/51674575/c-bad-alloc-exception-not-catched

// see godbolt

#include <iostream>

struct A {
    A() { std::cout << "A\n"; }
    A(const A&) { std::cout << "A(copy)\n"; }
    ~A() { std::cout << "~A\n"; }
};

int main() {
    try {
        throw A();
    } catch (const A& a) {
        std::cout << "caught! &a=" << &a << '\n';
    }
}
