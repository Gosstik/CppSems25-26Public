#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <tuple>

struct S {
    int n;
    std::string s;
    float d;

    // lexicographical comparison
    friend bool operator<(const S& lhs, const S& rhs) {
        return std::tie(lhs.n, lhs.s, lhs.d) < std::tie(rhs.n, rhs.s, rhs.d);
    }
};

int main() {
    std::set<S> set_of_s;

    S value{42, "Test", 3.14};
    std::set<S>::iterator iter;
    bool is_inserted;

    // Unpack pair
    std::tie(std::ignore, is_inserted) = set_of_s.insert(value);
    assert(is_inserted);

    // std::tie and structured bindings
    auto pos = [](int w) {
        return std::tuple(1 * w, 2 * w);
    };

    auto [x, y] = pos(1);
    assert(x == 1 && y == 2);
    std::tie(x, y) = pos(2);  // reuse x, y with tie
    assert(x == 2 && y == 4);

    // Implicit conversions are permitted
    std::tuple<char, short> coords(6, 9);
    std::tie(x, y) = coords;  // x and y are int
    assert(x == 6 && y == 9);
}
