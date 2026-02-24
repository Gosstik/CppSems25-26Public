#include <iostream>
#include <stdexcept>

// RAII --- Resource Acquisition Is Initialization
// Smart Pointers --- example of RAII in C++

// What problems does PtrWrapper have ???

struct BadPtrWrapper {               // smart ptr
    BadPtrWrapper(int* p) : p(p) {}  // NOLINT
    BadPtrWrapper(const BadPtrWrapper& other) = default;
    ~BadPtrWrapper() { delete p; }

    int* p;
};

////////////////////////////////////////////////////////////////////////////////

void Bar(int& rx) {
    if (rx % 2 == 1) {
        throw std::invalid_argument("only even values are acceptable");
    }
    rx *= 2;
}

void Foo(int x) {
    BadPtrWrapper pw = BadPtrWrapper(new int(x));
    Bar(*pw.p);
    // no delete
}

int main() {
    try {
        Foo(0);
        Foo(1);
    } catch (const std::exception& err) {
        std::cout << "Foo failed: " << err.what() << '\n';
    }
}
