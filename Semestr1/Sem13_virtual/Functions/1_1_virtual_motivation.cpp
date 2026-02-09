#include <iostream>

struct Base {
    int* b = new int(0);

    Base() { std::cout << "Base()\n"; }

    ~Base() {
        std::cout << "~Base()\n";
        delete b;
    }
};

struct Derived : Base {
    // int* d = new int(0);

    Derived() { std::cout << "Derived()\n"; }

    ~Derived() {
        std::cout << "~Derived()\n";
        // delete d;
    }
};

int main() {
    Derived* pd = new Derived();  // NOLINT
    Base* pb = pd;
    delete pb;  // out ???

    /// ...
}
