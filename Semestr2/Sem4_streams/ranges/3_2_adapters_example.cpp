#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>

namespace rng = std::ranges;
namespace vi = std::views;

int main() {
    auto good_numbers = vi::iota(0) | vi::filter([](auto x) {
                            return x % 3 == 0;
                        }) |
                        vi::transform([](auto x) {
                            return x * x;
                        }) |
                        vi::drop_while([](auto x) {
                            return x < 20;
                        });

    rng::copy(
        good_numbers | vi::take(5), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    rng::copy(  // !!! count again, first 5 values were not cached
      good_numbers | vi::take(10),
      std::ostream_iterator<int>(std::cout, " ")
  );
}
