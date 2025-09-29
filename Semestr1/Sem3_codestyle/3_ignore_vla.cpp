#include <iostream>

int main() {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvla-cxx-extension"
// #pragma GCC diagnostic warning "-Wvla-cxx-extension"
// #pragma GCC diagnostic error "-Wvla-cxx-extension"

    int n = 10;
    std::cin >> n;
    int arr[n];
    std::cout << arr[0] << '\n';

#pragma GCC diagnostic pop
}
