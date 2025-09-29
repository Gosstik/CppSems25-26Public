#include <iostream>

void Swap(int* lhs, int* rhs) {
  int tmp = *lhs;
  *lhs = *rhs;
  *rhs = tmp;
}

int main() {
    int x = 10;
    int y = 20;
    std::cout << x << ' ' << y << '\n';
    Swap(&x, &y);
    std::cout << x << ' ' << y << '\n';
}
