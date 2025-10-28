#include <cstdint>
#include <iostream>
#include <limits>

int main() {
    int64_t i64 = std::numeric_limits<int64_t>::max();
    int32_t i32 = i64;  // implementation defined behaviour, not UB

    // int64_t val = i64 + 1;
    std::cout << i32 << '\n';
}
