#include <iostream>

int& Foo() {
    static int a = 0;
    // int a = 0;
    ++a;
    std::cout << "Foo called " << a << " times" << std::endl;
    return a;
}

void Bar(int c) {
    static int a = c;
    std::cout << "Bar called " << a << " times" << std::endl;
}

int main() {
    int& v1 = Foo();
    int& v2 = Foo();

    std::cout << "Check equal: " << (v1 == v2) << '\n';

    Foo();
    Foo();

    std::cout << "\n";

    Bar(10);
    Bar(20);
    Bar(30);
}
