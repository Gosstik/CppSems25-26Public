#include <iostream>

int x = 1;

int Foo(int n) {
    if (n == 0) {
        return 0;
    }
    static int x = Foo(n - 1) + ::x;
    return x;
}

int main() {
    // Foo(3);
    std::cout << Foo(3) << " " << Foo(3) << std::endl; // ???
}
