#include <iostream>

void Foo(int) {
    std::cout << 1 << '\n';
}

void Foo(double) {
    std::cout << 2 << '\n';
}

int main() {
    long long val = 0;
    Foo(val); // ???
}
