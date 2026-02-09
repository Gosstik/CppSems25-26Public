#include <iostream>

// // CE
// template <typename... Args, typename T>
// struct S1 {};

// // CE
// template <typename... Args1, typename... Args2>
// struct S2 {};

// OK, but it is impossible to call that function :)
template <typename... Args, typename T>
void Foo() {
    std::cout << "Foo\n";
}

// OK,
template <typename... Args1, typename... Args2>
void Bar() {
    std::cout << "Bar\n";
}

// OK, that function can be called only if you specify all Args manually
// and make compiler deduce T.
template <typename... Args, typename T>
void Baz(Args... vals, T t) {
    std::cout << "Baz\n";
}

int main() {
    // Foo<int>();
    Bar<int>();
    Baz<int>(1, 2.0);
}
