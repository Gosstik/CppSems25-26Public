#include <iostream>

// operator requires (requires expression)

template <typename T>
void TestAdd() {
    static constexpr bool res = requires(T a, T b) { a + b; };
    // static_assert(res); // You may use it
    std::cout << res;
}

template <typename T>
    requires requires(T a, T b) {
        a + b;
        a - b;
}
T Add(const T& a, const T& b) {
    return a + b;
}

int main() {
    TestAdd<int>();
    TestAdd<void>();
    TestAdd<decltype(std::cout)>();
    std::cout << '\n';
}
