#include <iostream>

struct Mother {
    virtual void Foo() { std::cout << x; }

    int x = 0;
};

struct Father {
    int y = 1;
    virtual void Bar() { std::cout << y; }
};

struct Son : Mother, Father {
    int z = 2;
    void Foo() override { std::cout << z; }
    void Bar() override { std::cout << z; }
};

struct S {
    int64_t a;
    int64_t b;
};

int main() {
    {
        void (Mother::*p)() = &Mother::Foo;

        Son son;
        Mother& m = son;
        (m.*p)();  // out: 2
    }

    void (Son::*p)() = &Son::Bar;

    Son son;
    (son.*p)();

    std::cout << sizeof(p) << '\n';
    S s = reinterpret_cast<S&>(p);
    std::cout << sizeof(s) << ' ' << s.a << ' ' << s.b << '\n';
}
