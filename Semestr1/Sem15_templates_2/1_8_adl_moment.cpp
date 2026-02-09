#include <iostream>

struct X {
    operator long() { return 42; }
};

void Foo(long) { std::cout << 1 << '\n'; }

template <typename T>
void Bar(T val) {
    Foo(val);
}

void Foo(X) { std::cout << 2 << '\n'; }

int main() {
    X x;
    Bar(x);  // ???
}
