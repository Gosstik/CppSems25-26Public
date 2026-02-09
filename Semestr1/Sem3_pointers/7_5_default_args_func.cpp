#include <iostream>

// Output ???

int Foo() {
    static int x = 0;
    ++x;
    std::cout << x << std::endl;
    return x;
}

void Bar(int = Foo()) {}

int main() {
    Bar();
    Bar();
}
