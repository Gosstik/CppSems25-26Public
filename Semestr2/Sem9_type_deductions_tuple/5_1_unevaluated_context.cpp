#include <iostream>

int main() {
    int x = 0;
    decltype((x += 10) - 1) y = 1;
    std::cout << x << ' ' << y << '\n';
}
