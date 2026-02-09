#include <iostream>

int Foo(int x) { return x; }

int Foo(int x, int y, int z) { return x + y + z; }

int Foo(int x, int y, int z, int t) { return x + y + z + t; }

template <typename... T>
int F1(T... args) {
    return Foo(Foo(args...) + Foo(args)...);
    // return (Foo(Foo(args) + Foo(args)), ...);
    // Foo((Foo(1) + Foo(1)), Foo(Foo(2) + Foo(2)), Foo(Foo(3) + Foo(3)))
}

template <typename... T>
int F2(T... args) {
    return Foo(Foo(args, args...)...);
}

int main() {
    std::cout << F1(1, 2, 3) << '\n';  // ???
    // std::cout << F2(1, 2, 3) << '\n';  // ???
}
