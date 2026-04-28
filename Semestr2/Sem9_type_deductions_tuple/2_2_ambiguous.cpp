#include <iostream>
#include <vector>

// Type conversion does not work for deduction
auto Foo(int x) {
    if (x > 0) {
        return 1;
    }
    return 1u;
}

template <typename T>
void Debug(T x) = delete;

int main() {
    auto i = true ? -1 : 1u;
    // auto v = true ? std::vector<int>{} : std::vector<int64_t>{};
    // Debug(i);
    std::cout << i << '\n';
}
