#include <iostream>
#include <tuple>

// Unpack tuple with structured bindings (since c++17)

// !!! Not only tuples can be unpacked with structured bindings.
// https://en.cppreference.com/w/cpp/language/structured_binding

int main() {
    std::tuple<int, double, char> t{1, 2.0, 'a'};

    auto&& [la, lb, lc] = t;
    auto&& [ra, rb, rc] = std::move(t);

    std::cout << std::get<1>(t) << '\n';
    rb = 5.0;
    std::cout << std::get<1>(t) << '\n';

    // range based for
}
