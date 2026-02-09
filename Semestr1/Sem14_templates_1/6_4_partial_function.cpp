// Funcs do not have partial spec, but that behaviour can be achieved by class
// static methods.

// Sutter trick

#include <iostream>

template <typename T>
struct FooImpl {
    static int Foo(T) { std::cout << 1; }
};

template <typename T>
struct FooImpl<T*> {
    static int Foo(T*) { std::cout << 2; }
};

template <typename T>
int Foo(T) {
    FooImpl<T>::Foo(T());
}

int main() {
    int a{};
    Foo(a);   // 1
    Foo(&a);  // 2
}
