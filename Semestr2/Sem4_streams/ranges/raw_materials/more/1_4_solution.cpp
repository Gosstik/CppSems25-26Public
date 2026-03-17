#include <algorithm>
#include <iostream>
#include <ranges>

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
    // Non-owning view
    auto v = ranges::istream_view<int>(std::cin) | views::filter([](int n) {
                 return n < 5;
             }) |
             views::transform([](int n) {
                 return n * 2;
             });
    ranges::copy(v, std::ostream_iterator<int>{std::cout, " "});
}
