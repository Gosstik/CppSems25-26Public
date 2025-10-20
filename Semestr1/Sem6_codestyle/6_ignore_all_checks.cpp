// NOLINTBEGIN
// clang-format off

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-pedantic"

#include <iostream>


int a = 0;

struct global_struct {
    static const int magic = 10;
};


int main() {
    int n, k;
    std::cin >> n >> k;

    int arr[n];

    std::cout << "Hello, world!\n"
             << arr[0]
             << std::endl;
}

// clang-format on
// NOLINTEND
