#include <cstdint>

// Concepts

// Named requirements

// Iterator
// RandomAccessIterator
// Allocator
// SequenceContainer

// Not satisfied to Names requirement == UB

template <typename T, uint64_t N> requires (N <= 10)
class SmallArray {

};

// constexpr
// consteval
// constinit --- initialization in CT, but can be modified
