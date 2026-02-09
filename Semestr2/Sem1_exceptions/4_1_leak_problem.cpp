#include <iostream>
#include <stdexcept>

// try with -fsanitize=address

void Bar(int& rx) {
    if (rx % 2 == 1) {
        throw std::invalid_argument("only even values are acceptable");
    }
    rx *= 2;
}

void Foo(int x) {
    int* px = new int(x);
    Bar(*px);
    delete px;
}

int main() {
    try {
        Foo(0);
        Foo(1);
    } catch (const std::exception& err) {
        std::cout << "Foo failed: " << err.what() << '\n';
    }
}
