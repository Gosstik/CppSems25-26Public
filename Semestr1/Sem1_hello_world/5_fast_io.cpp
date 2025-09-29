#include <iostream>
#include <vector>

int main() {
    // Fast io
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    // Input
    size_t n{};
    std::cin >> n;
    std::vector<int64_t> a(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Print squares of a
    for (size_t i = 0; i < n; ++i) {
        std::cout << a[i] * a[i] << ' ';
    }
    std::cout << '\n';
}
