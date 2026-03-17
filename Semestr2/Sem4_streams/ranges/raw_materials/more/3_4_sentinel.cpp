#include <ranges>

namespace ranges = std::ranges;

int Accumulate(const ranges::input_range auto& coll) {
    int acc = 0;
    for (auto& elem : coll) {
        acc += elem;
    }
    return acc;
}

template <auto V>
struct EndValue {
    bool operator==(auto)
};

int main() {}
