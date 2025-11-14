#include <iostream>

void Swap(int& lhs, int& rhs) {
    int tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

int main() {
    int x = 1;
    int y = 2;
    Swap(x, y);
    std::cout << x << ' ' << y << '\n';
}
