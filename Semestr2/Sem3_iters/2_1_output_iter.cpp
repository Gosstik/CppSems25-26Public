#include <algorithm>
#include <iostream>
#include <vector>

// LegacyOutputIterator:
// https://en.cppreference.com/w/cpp/named_req/OutputIterator
// Comparison with other iters:
// https://en.cppreference.com/w/cpp/iterator

// std::set_intersection
// https://en.cppreference.com/w/cpp/algorithm/set_intersection

int main() {
    int a[10] = {1, 2, 3, 4, 5};
    std::vector<int> v;
    std::copy(a, a + 10, v.begin());

    // print
    for (auto val : v) {
        std::cout << val << ' ';
    }
    std::cout << '\n';
}
