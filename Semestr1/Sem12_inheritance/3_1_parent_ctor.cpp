#include <iostream>

struct Base {
    // Base() = default;
    explicit Base(int x) : x(x) {}

    int x;
};

struct Derived : Base {
    explicit Derived(double y) : y(y) {}  //* CE

    double y;
};

int main() {
    Derived d = 3.14;  //* CE, even if Derived ctor is correct
    std::cout << d.y << '\n';
}
