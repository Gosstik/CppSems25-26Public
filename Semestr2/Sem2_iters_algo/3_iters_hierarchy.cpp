#include <iostream>
#include <iterator>

// clang-format off

//// Hierarchy:
// Input                     (single pass algorithms, supports only ++ (prefix and postfix))
// Forward                   (supports only ++)
// Bidirectional             (supports ++ and --)
// Random Access             (supports all operations as raw pointer)
// Contiguous (since C++17)  (logical layout of elements coincide with layout in memory)

// Output --- separate category, from [iterator.requirements.general]:
// Iterators that further meet the requirements of output iterators are called mutable iterators.
// Nonmutable iterators are referred to as constant iterators.

// That means that only mutable forward iterator satisfies both input and output iterator.

// Requirements for each category: https://en.cppreference.com/w/cpp/iterator

// All the categories of iterators require only those functions that are
// realizable for a given category in constant time (amortized)

// C++23 standard
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf
// 25.3 [iterator.requirements]

// Legacy iterator: https://en.cppreference.com/w/cpp/named_req/Iterator
// Examine other categories and their requirements (refs in LegacyIterator).

// Instead of being defined by specific types, each category of iterator is
// defined by the operations that can be performed on it. This definition means
// that any type that supports the necessary operations can be used as an
// iterator -- for example, a pointer supports all of the operations required by
// LegacyRandomAccessIterator, so a pointer can be used anywhere a
// LegacyRandomAccessIterator is expected.

// compiler can make vectorized optimizations for contiguous iterators

// clang-format on

int main() {}
