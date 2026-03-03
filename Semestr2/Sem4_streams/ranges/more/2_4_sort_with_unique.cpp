#include <algorithm>
#include <iostream>
#include <vector>

namespace rng = std::ranges;

int main() {
    std::cout << "HERE\n";
    std::vector<int> vec = {1, 4, 3, 8, 5, 2};

    //// Sort array
    // auto se = rng::sort(vec);
    // for (auto it = rng::begin(vec); it != se; ++it) {
    //   std::cout << *it << ' ';
    // }

    //// Move unique elements to the left part of vector
    auto [e, l] = rng::unique(rng::begin(vec), rng::sort(vec));
    for (auto it = vec.begin(); it != e; ++it) {
        std::cout << *it << ' ';
    }

    //// Iterate over repeating elements
    // for (auto val: rng::unique(rng::begin(vec), rng::sort(vec))) {
    //   std::cout << val << ' ';
    // }
}
