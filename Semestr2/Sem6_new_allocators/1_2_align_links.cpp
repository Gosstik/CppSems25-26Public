// operator alignof
// https://en.cppreference.com/w/cpp/language/alignof

// operator alignas
// https://en.cppreference.com/w/cpp/language/alignas

// aligned_alloc
// https://en.cppreference.com/w/cpp/memory/c/aligned_alloc

// malloc always align memory as alignas(std::max_align_t)
// https://en.cppreference.com/w/cpp/types/max_align_t

// std::align
// https://en.cppreference.com/w/cpp/memory/align

// ??? Why do we need alignment more than std::max_align_t?
// 1. SSE (256), AVX (512) operations --- performance optimizations
