#include <iostream>

// !!! sizeof() works at compile time !!!

void Foo(int arr[10]) {
    std::cout << "Foo, sizeof(arr)=" << sizeof(arr) << '\n';  // 8
}

void Bar(int (&arr)[10]) {
    std::cout << "Bar, sizeof(arr)=" << sizeof(arr) << '\n';  // 40
}

// Does not work with define !!!
using ArrInt11 = int[11];

void Baz(ArrInt11& arr) {
    std::cout << "Baz, sizeof(arr)=" << sizeof(arr) << '\n';  // 44
}

int main() {
    int arr10[10]{};
    Foo(arr10);
    Bar(arr10);  // OK

    int arr11[11]{};
    // Bar(arr11);  // CE
    Baz(arr11);  // OK
}
