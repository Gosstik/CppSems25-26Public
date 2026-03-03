#include <iostream>
#include <iterator>

// Last is not always a valid Input iterator
// In most cases it is singular (uninitialized) iterator.

template <typename InputIt, typename UnaryFunc>
UnaryFunc ForEach(InputIt first, InputIt last, UnaryFunc f) {
    for (; first != last; ++first) {
        f(*first);
    }
    return f;
}

// Define range as a pair of iterators is not a goo idea.
// Solution in std::ranges: range is iterator + sentinel (guard, limiter)

int main() {
    ForEach( // In fact it is TransformCopyIf(...)
      std::istream_iterator<int>{std::cin},
      std::istream_iterator<int>{},
      [](int d) {
        if (d < 5) {
          std::cout << 2 * d << " ";
        }
      }
  );
}
