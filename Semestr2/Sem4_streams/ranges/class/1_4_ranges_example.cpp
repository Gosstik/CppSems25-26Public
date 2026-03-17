#include <ranges>
#include <vector>
#include <algorithm>
#include <iostream>

// range - something that has std::ranges::begin() and std::ranges::end()
// view - movable range

// Ranges library (since C++20)
// https://en.cppreference.com/w/cpp/ranges.html

namespace ranges = std::ranges; // algorithms and concepts
namespace views = std::views; // lazy adapters

// template <typename View1, typename View2>
// View2 operator|(View1 v1, View2 v2) {
//     return v2(v1);
// }

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // View adaptors (lazy, composable)
    auto result = vec
        | std::views::filter([](int n) { return n % 2 == 0; })
        | std::views::transform([](int n) { return n * n; })
        | std::views::take(3);

    std::ranges::copy(result, std::ostream_iterator<int>{std::cout, " "});

    // std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>{std::cout, " "});
    // std::ranges::copy(vec, std::ostream_iterator<int>{std::cout, " "});
}
