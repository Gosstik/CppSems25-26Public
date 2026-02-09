#include <iostream>

template <typename T>
void Foo() {
    static int stat = 0;
    std::cout << ++stat << '\n';
}

int main() {
    Foo<int>();
    Foo<int>();
    Foo<const int>();
}
