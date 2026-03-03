#include <algorithm>
#include <concepts>
#include <functional>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

namespace rng = std::ranges;
namespace vi = std::views;

// using iterator_t = decltype(rng::begin(declval<T&>()))
// using sentinel_t = decltype(rng::end(declval<T&>()))

//// Concepts
// range = rng::begin<T> + rng::end<T>
// input_range = range<T> + input_iterator<T>
// forward_range = forward_range<T> + forward_iterator<iterator_t<T>>
// ...
// random_access_range = ...

// !!! rng::less vs std::less

// no requirements for sentinel (separate concept)
template <
    rng::random_access_range R,
    class Comp = rng::less,
    class Proj = std::identity>
    requires std::sortable<rng::iterator_t<R>, Comp, Proj>
rng::borrowed_iterator_t<R> Sort(
    R&& r, Comp comp = Comp{}, Proj proj = Proj{}) {
    return {};
}

struct Point {
    int x;
    int y;
};

int main() {
    // We may choose: complex comparator or projector
    std::vector<Point> v;
    rng::sort(v, [](auto&& a, auto&& b) {
        return a.x < b.x;
    });
    rng::sort(v, {}, [](auto&& a) {
        return a.x;
    });
    // now is less speedy, but projector must give more freedom for optimization
    // Try with Quick Bench
    rng::sort(v, {}, &Point::x);  // with std::invoke

    // With transform speed advantage is obvious
    std::vector<int> v_out;
    auto out = std::back_inserter(v_out);
    std::transform(v.begin(), v.end(), out, [](const auto& a) {
        return a.x * 2;
    });
    rng::transform(
        v,
        out,
        [](auto x) {
            return x * 2;
        },
        &Point::x);
}
