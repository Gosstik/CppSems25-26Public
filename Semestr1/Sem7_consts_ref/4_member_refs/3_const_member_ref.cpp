#include <iostream>

struct S {
    const int& r = 1;
    S() : r(5) {}
};

int main() {
    S s;
    std::cout << s.r << '\n';  // ???
}
