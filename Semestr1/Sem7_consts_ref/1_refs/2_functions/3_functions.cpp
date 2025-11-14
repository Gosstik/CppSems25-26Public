#include <iostream>

// OK, CE, RE, UB ???

int& Foo() {
    int* p = new int(1);
    return *p;
}

int main() {
    int x = Foo();
    std::cout << x << '\n';
    delete &x;  // ???
}
