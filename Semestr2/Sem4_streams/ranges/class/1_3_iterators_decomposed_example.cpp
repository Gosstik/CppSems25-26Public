#include <vector>
#include <iostream>

// clang-format off

// Disadvantages:
// 1) We create vector "result", allocate memory but actually do not need to use that vector later.
// 2) We iterate 2 times instead of 1 (requires more time)

// Solution: want lazy combiners.

// clang-format on

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::vector<int> result;

    // Make even
    for (auto v: vec) {
        if (v % 2 == 0) {
            result.push_back(v);
        }
    }

    // Square
    for (auto& n: result) {
        n *= n;
    }

    // Limit
    result.resize(3);

    // Output
    for (auto n: result) {
        std::cout << n << " ";
    }
}
