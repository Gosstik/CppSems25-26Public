#include <iostream>

// mutable keyword

// UB ???

struct S {
    /*mutable*/ int x = 1;
    int& rx = x;  // can be modified in const methods !!!!!!!
    char* str = new char[10]{'a'};

    void ConstMethod() const {
        ++x;            // CE
        ++rx;           // OK
        str[0] = 'b';   // OK
        str = nullptr;  // CE
    }

    void PrintX() const { std::cout << x << '\n'; }

    ~S() { delete[] str; }
};

int main() {
    const S s;
    ++s.x;
    ++s.rx;

    s.PrintX();
    s.ConstMethod();
    s.PrintX();
}
