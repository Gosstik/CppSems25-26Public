#include <iostream>

// Remember the rule:
// !!! Outer array always casts to pointer (array-to-pointer convertion)

// Cases 1 and 2 perform array to pointer conversion.
// Case 3 cannot perform that conversion, because outer type is pointer

// 1
void Foo(int** a) { std::cout << 1 << '\n'; }

// 2
void Foo(int* a[5]) { std::cout << 2 << '\n'; }

// 3 (different, but also point to the first element)
void Foo(int (*a)[5]) { std::cout << 3 << '\n'; }

// 4
void Foo(int*(*a)) { std::cout << 3 << '\n'; }

int main() {
    int a[5];
    Foo(&a);  // ???

    int* b = a;
    Foo(&b);  // ???

    int c[5][5];
    Foo(c);  // ???
}
