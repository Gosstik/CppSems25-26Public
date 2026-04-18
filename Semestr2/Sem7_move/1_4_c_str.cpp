#include <iostream>

using StrType = const char[10];
// using StrType = const char*;

// void Foo(const char (&arr)[10]) { ... }// OK
void Foo(StrType& arr) { std::cout << "lvalue\n"; }

void Foo(StrType&& arr) { std::cout << "rvalue\n"; }

int main() {
    Foo("123456789");  // lvalue
}
