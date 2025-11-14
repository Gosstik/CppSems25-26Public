#include <iostream>

int x = 0;

struct S {
    int& r = x;

    S(int& y) { r = y; }
    // S(int& y) : r(y) { r = y; }
};

int main() {
    int y = 1;
    S s(y);
    ++s.r;
    std::cout << x << y << s.r;  // ???
}
