#include <iostream>

enum /*class*/ E {
    White = 1,
    Gray,
    Black = 1,
};

enum /*class*/ E2 {
    Pink = 1,
    Yellow,
    Black = 1,
};

int main() {
    int e = White;
    // E e = E::White;
    std::cout << e << '\n';

    E val = E::White;
    E val2 = E(1);

    // int64_t e = E::Black;
    // E e = E::White;
    // std::cout << e << '\n';
    std::cout << (E::White == E::Black) << '\n';
}
