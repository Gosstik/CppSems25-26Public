#include <iostream>

struct Base {
    int b = 42;
};

struct Im : protected Base {};

struct Derived : Im {
    int d = 5;

    void Foo(Im i) {
        Base& b = i;                          // OK
        std::cout << b.b << std::endl;        // OK
        std::cout << i.b << std::endl;        // CE
        std::cout << i.Base::b << std::endl;  // OK !!!
    }
};

int main() {
    Derived d;
    Im i;

    // ??? How to fix CE ?
    //* 1) replace protected inheritance with public
    //* 2) add 'friend int main();' to Im
    Base& b = i;                          // CE
    std::cout << i.Base::b << std::endl;  // CE !!!
    d.Foo(i);

    return 0;
}
