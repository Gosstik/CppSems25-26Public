#include <iostream>
#include <unordered_map>
#include <string>
#include <array>
#include <vector>
#include <utility>
#include <tuple>

// tuple-like types
// arrays
// simple structures

struct Point {
    std::vector<std::string> names;
    std::vector<int> ages;
};

namespace std {

template <>
struct tuple_size<Point> : std::integral_constant<std::size_t, 2> {};

template <>
struct hash<Point> {
    size_t operator()(const Point& s) const noexcept {
        return 1;
    }
};

} // std

int main() {
    // S s{
    //     .names = {"a", "b", "c"},
    //     .ages = {1, 2, 3},
    // };

    // auto& [names, ages] = s;

    ////////////////////////////////////////////////////////////////////////////

    std::tuple<int, bool, std::string> t{1, true, "hello"};
    auto& [i, b, s] = t;
    auto& out = std::get<std::string>(t);
    out = "world";
    std::cout << std::get<2>(t) << '\n';

    std::tuple<bool, bool> t2;
    std::pair<bool, bool> p2;
    auto& out2 = std::get<bool>(t2);
    auto& out2 = std::get<bool>(t2);

    ////////////////////////////////////////////////////////////////////////////

    std::unordered_map<Point, int> um;
    int x;
    int y;

    using std::swap;
    swap(x, y);

    std::swap(x, y);
}
