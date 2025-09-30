#include <iostream>

void Foo(int a = 10, int b = 20) {
    std::cout << a << ' ' << b << '\n';
}

//// CE, redefinition
// void Foo(int a, int b = 10);

//// CE, all subsequent parameters must have a default argument
// void Bar(int a = 10, int b);

int main() {
    Foo(1, 2);
    Foo(1);
    Foo();
}
