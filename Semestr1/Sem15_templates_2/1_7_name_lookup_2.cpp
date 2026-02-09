#include <iostream>

void Foo(long) { std::cout << 1 << '\n'; }

template <typename T>
void Bar(T val) {
    Foo(val);
}

void Foo(int) { std::cout << 2 << '\n'; }

int main() {
    Bar(0l);  // ???
    Bar(0);   // ???
}
