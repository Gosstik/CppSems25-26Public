#include <iostream>

struct Base {
    int a = 0;
};

struct Derived : private Base {
    // friend int main(); // even it won't work: [except.handle] (c++23)

    int a = 1;
};

int main() {
    try {
        throw Derived{};  // NOLINT
    } catch (const Base& obj) {
        std::cout << "Base\n";
    } catch (...) {
        std::cout << "...\n";
    }
}
