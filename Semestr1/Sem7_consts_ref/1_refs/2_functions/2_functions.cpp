#include <iostream>

// Try with clang++ -std=c++23

int& Foo(int& x) {
    int y = ++x;  //* try to make it static
    return y;
}

int main() {
    int x = 0;
    int& y = Foo(x);
    y = 2;
    std::cout << x << ' ' << y << '\n';  // ???
}
