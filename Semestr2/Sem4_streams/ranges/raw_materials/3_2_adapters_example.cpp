#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>

namespace ranges = std::ranges;
namespace views = std::views;

int main() {
    auto good_numbers = views::iota(0) | views::filter([](auto x) {
                            return x % 3 == 0;
                        }) |
                        views::transform([](auto x) {
                            return x * x;
                        }) |
                        views::drop_while([](auto x) {
                            return x < 20;
                        });

    ranges::copy(
        good_numbers | views::take(5),
        std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    ranges::copy(  // !!! count again, first 5 values were not cached
      good_numbers | views::take(10),
      std::ostream_iterator<int>(std::cout, " ")
  );
}
