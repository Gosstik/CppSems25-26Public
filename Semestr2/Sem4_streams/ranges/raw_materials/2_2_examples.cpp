#include <algorithm>
#include <iostream>
#include <ranges>
#include <sstream>
#include <utility>

// TODO: purpose?
void EmptyView() {
    std::ranges::empty_view<int> v;  // type is required
}

////////////////////////////////////////////////////////////////////////////////

void SingleView() {
    std::ranges::single_view v(10);
    for (auto x : v) {
        std::cout << x;
    }

    // e.g. atomic, mutex
    std::ranges::single_view<std::string> v2(std::in_place_t{}, "abc");
    for (const auto& x : v2) {
        std::cout << x;
    }
}

////////////////////////////////////////////////////////////////////////////////

// Iota --- Greek letter
// https://en.wikipedia.org/wiki/Iota

// APL (Array Programming Language)
// https://en.wikipedia.org/wiki/APL_(programming_language)
// В те времена монитор себе могли позволить полтора землекопа...

void IotaView() {
    std::ranges::iota_view v(1, 5);
    for (auto x : v) {
        std::cout << x << ' ';  // 1 2 3 4
    }

    std::ranges::iota_view vinf(1);  // 1 2 3 4 ...
    // std::ranges::iota_view(1).end() == std::unreachable_sentinel{}
}

////////////////////////////////////////////////////////////////////////////////

void IstreamView() {
    auto floats = std::istringstream{"1.1  2.2\n3.3\n4.4\n55\n66"};
    std::ranges::copy(
        std::ranges::istream_view<float>(floats),
        std::ostream_iterator<float>{std::cout, " "});
    std::cout << '\n';
}
