#include <iostream>
#include <iterator>

template <
    typename InputIt,
    typename OutputIt,
    typename UnaryPred,
    typename UnaryFunc>
OutputIt TransformCopyIf(
    InputIt first,
    InputIt last,
    OutputIt d_first,
    UnaryPred pred,
    UnaryFunc func) {
    // ...
    return d_first;
}

int main() {
    // usage (hard to read)
    TransformCopyIf(
        std::istream_iterator<int>{std::cin},
        std::istream_iterator<int>{},
        std::ostream_iterator<int>{std::cout},
        [](int n) {
            return n < 5;
        },
        [](int n) {
            return n * 2;
        });
}
