#include <iostream>

template <typename T>
void Foo(T) {
    std::cout << "T";
}

struct S {};

// void Foo(S) { std::cout << "S"; }

template <typename T>
void CallFoo(T a, S b) {
    Foo(a);  // ???
    Foo(b);  // ???
}

void Foo(S) { std::cout << "S"; }

int main() {
    S s;
    CallFoo(s, s);
}
