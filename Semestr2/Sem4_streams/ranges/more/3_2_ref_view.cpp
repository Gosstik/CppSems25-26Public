#include <iostream>
#include <ranges>
#include <string>
#include <string_view>

// Range adaptors
// vi::all()
// rng::subrange

namespace vi = std::views;

struct Empty {
    int* begin() { return nullptr; }
    int* end() { return nullptr; }
};

int main() {
    std::string s = "abc";
    auto sv = vi::all(s);     // rng::ref_view<string>
    auto sagain = sv.base();  // std::string

    Empty e;
    auto ev = vi::all(e);  // OK
}
