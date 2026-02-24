// clang-format off

#include <algorithm>

// Most used

// copy
// copy_backward
// copy_if (UnaryPredicate)
// fill
// unique (requires sorted range)

// ??? Why forward iterator (both input and output are not enough) ???
// input - no rule for *i = o
// output - no operator!=()
// mutable forward - satisfies both input and output
// !!! In standard in declaration there is just ForwardIterator, but from [alg.fill]:
// Mandates: The expression value is writable (25.3.1) to the output iterator.
// And library implementation actually check _Mutable_ForwardIteratorConcept<_ForwardIterator>

// Simple

// find
// find_if
// count
// count_if
// all_of
// any_of
// for_each

// More complex

// remove
// remove_if
// replace
// replace_if
// binary_search

// Even more complex

// sort (see libstdc++ impl)
// stable_sort (see libstdc++ impl and stl_tempbuf.h https://github.com/gcc-mirror/gcc/blob/d9375e490072d1aae73a93949aa158fcd2a27018/libstdc%2B%2B-v3/include/bits/stl_tempbuf.h to explain log^2)
// partition: https://en.cppreference.com/w/cpp/algorithm/partition

// Complex (what iterator types are required ???)

// is_permutation (Forward)
// next_permutation (Bidirectional, with impl)
// is_heap (Random Access)
// make_heap (Random Access)
// rotate (Forward, but RA has better performance; example + examine impl: https://en.cppreference.com/w/cpp/algorithm/rotate#Possible_implementation). next_read = next_mid (2 cases depending on mid, always cut off the start)
// reverse (Bidirectional)

// clang-format on

int main() {

}
