#include <cassert>
#include <iostream>
#include <tuple>

struct Point {
    int x{};
    int y{};
    int z{};

    Point() = default;
    Point(int x, int y, int z) : x(x), y(y), z(z) {}

    friend bool operator==(const Point& lhs, const Point& rhs) noexcept {
        return std::tie(lhs.x, lhs.y, lhs.z) == std::tie(rhs.x, rhs.y, rhs.z);
    }

    friend bool operator<(const Point& lhs, const Point& rhs) noexcept {
        return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
    }
};

int main() {
    {
        Point s1{1, 1, 1};
        Point s2{1, 1, 1};
        Point s3{1, 1, 0};

        assert(s1 == s2);
        assert(!(s1 == s3));
    }

    {
        Point s1{1, 2, 3};
        Point s2{1, 3, 0};

        assert(s1 < s2);
        assert(!(s2 < s1));
    }

    std::cout << "OK" << std::endl;
}
