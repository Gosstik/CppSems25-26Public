#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// Disadvantages:
// 1) We create vector, allocate memory but actually do not need to use
// that vector later.
// 2) We iterate 2 times instead of 1 (requires more time)

// Positive moments: std algorithms may vectorize operations.

// Solution: want lazy combiners.

int main() {
    std::vector<int> v;
    std::istream_iterator<int> start{std::cin}, fin{};
    std::ostream_iterator<int> d_start{std::cout, " "};

    std::copy_if(start, fin, std::back_inserter(v), [](int n) {
        return n < 5;
    });
    std::transform(v.begin(), v.end(), d_start, [](int n) {
        return n * 2;
    });
}
