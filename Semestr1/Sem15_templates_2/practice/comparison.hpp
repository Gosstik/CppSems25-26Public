#pragma once

#include <iostream>
#include <map>
#include <string>

// std::less
// std::greater

struct MyType {
    std::string name;
    size_t value;

    // friend bool operator<(const MyType& lhs, const MyType& rhs) noexcept =
    // default;
};

template <typename T>
struct less {  // NOLINT
    constexpr bool operator()(const T& lhs, const T& rhs) const {
        return lhs < rhs;
    }
};

template <typename T>
struct greater {  // NOLINT
    constexpr bool operator()(const T& lhs, const T& rhs) const {
        return rhs < lhs;
    }
};

template <typename T>
struct equal {  // NOLINT
    constexpr bool operator()(const T& lhs, const T& rhs) const {
        return rhs < lhs;
    }
};

void TestComparison() {
    std::map<MyType, int> map;
    map.insert({{"abs", 1}, 1});  // CE without operator<()
}
