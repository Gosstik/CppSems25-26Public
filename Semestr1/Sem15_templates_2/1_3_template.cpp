#include <array>
#include <iostream>

template <typename T>
struct S {
    template <int N>
    void Foo(int) {}
};

template <>
struct S<double> {
    const int Foo = 1;
};

template <typename T>
void Bar(int x, int y) {
    S<T> s;
    s.Foo<5>(x + y);
}

int main() {
    Bar<double>(2, 3);  // OK
    // Bar<int>(2, 3);     // CE
}
