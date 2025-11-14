#include <iostream>

// Constructor == Ctor
// Destructor == Dtor

// Rule of three:
// 1) Copy Ctor
// 2) Copy Assignment
// 3) Dtor
// If one of that methods is non-trivial, likely all should be non-trivial

struct S {
    // Ctor from 0 argumants
    S() {}
    // Ctor from 1 int
    S(int x) {
        inner = x;
    }

    // Copy ctor
    S(const S& other) { /* ... */ }
    // S(S& other) {} // possible, also copy ctor
    // S(S other) {} // !!! CE

    S& operator=(const S& other) {
        inner = other.inner;
        return *this;
    }

    // Dtor
    ~S() {}

    int inner;
};

int main() {
    S s1;
    S s2(1); // S(int)
    S s3(s1); // S(const S&)
    S s4 = s2; // !!! S(const S&)
    s2 = s4; // operator=(const S&)
}
