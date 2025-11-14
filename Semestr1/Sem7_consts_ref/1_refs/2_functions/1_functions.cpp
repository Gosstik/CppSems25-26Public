#include <iostream>

int& Foo(int& x) { return ++x; }

int main() {
    int x = 0;
    Foo(x) = 2;
    int& rt = Foo(x);
    int t = Foo(x);

    std::cout << rt << ' ' << t << std::endl; // ???
}
