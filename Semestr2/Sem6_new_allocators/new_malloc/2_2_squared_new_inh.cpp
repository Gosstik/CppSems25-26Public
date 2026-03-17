#include <iostream>

// Do not use new[]

struct Base {
    Base() { std::cout << "Base()\n"; }

    // virtual dtor will not help to delete[]. Only ~Base() will be called
    virtual ~Base() { std::cout << "~Base()\n"; }
};

struct Derived : Base {
    Derived() { std::cout << "Derived()\n"; }

    ~Derived() {
        std::cout << "~Derived()\n";
        delete a;
    }

    int* a = new int(0);  // to cause leak
};

int main() {
    Base* bs = new Derived[5];
    delete[] bs;

    // Base* b = new Derived();
    // delete b;
}
