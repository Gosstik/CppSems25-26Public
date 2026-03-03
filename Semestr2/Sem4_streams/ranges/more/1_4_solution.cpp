#include <algorithm>
#include <iostream>
#include <ranges>

namespace rng = std::ranges;
namespace vi = std::views;

int main() {
    // Non-owning view
    auto v = rng::istream_view<int>(std::cin) | vi::filter([](int n) {
                 return n < 5;
             }) |
             vi::transform([](int n) {
                 return n * 2;
             });
    rng::copy(v, std::ostream_iterator<int>{std::cout, " "});
}
