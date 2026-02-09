#include <iostream>

struct S {
    int x = 1;
    int z = 2;
    double y = 2.0;

    void Foo(int z) {
        ++x;
        std::cout << x + z << '\n';
    }

    void Bar(int z) const { std::cout << x + z << '\n'; }
};

int main() {
    {
        int S::* p = &S::x;
        S s;
        std::cout << s.*p << '\n';

        S* ps = &s;
        std::cout << ps->*p << '\n';

        void (S::*pf)(int) = &S::Foo;
        // s.*pf(3); // CE
        (s.*pf)(3);

        void (S::*pcf)(int) const = &S::Bar;
        (s.*pcf)(6);

        // pf = pcf; // CE
        // pcf = pf; // CE
    }
}
