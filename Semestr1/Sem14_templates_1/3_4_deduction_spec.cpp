#include <iostream>

// https://cppinsights.io/

template <typename T>
T Min(T a, T b) {
    return a < b ? a : b;
}

template <typename T>
T Max(T& a, T& b) {
    return a < b ? a : b;
}

int main() {
    {
        // cut cv

        const int& a = 1;
        const int& b = 2;
        // Min<int>(int a, int b);
        std::cout << Min(a, b) << std::endl;
    }

    {
        int t = 0;
        int& x = t;
        int& y = t;

        // Max<int>(int& a, int& b);
        std::cout << Max(t, t) << std::endl;

        // Max<int>(int& a, int& b);
        std::cout << Max(x, y) << std::endl;

        // Max<int&>(int& a, int& b);
        std::cout << Max<int&>(x, y) << std::endl;

        const int& a = 1;
        const int& b = 2;
        // Max<const int>(const int& a, const int& b);
        std::cout << Max(a, b) << std::endl;
    }
}
