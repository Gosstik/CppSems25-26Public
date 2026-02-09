#include <iostream>

struct A {
    A() { std::cout << "A\n"; }
    A(const A&) { std::cout << "A(copy)\n"; }
    ~A() { std::cout << "~A\n"; }
};

void Bar(bool is_thrown) {
    A a;
    if (is_thrown) {
        throw a;  // NOLINT
    }
}

void Foo(bool is_thrown) {
    try {
        Bar(is_thrown);
    } catch (const A& a) {
        std::cout << "caught in Foo! &a=" << &a << '\n';
        throw;  // rethrow without copy
        // throw a; // new exception, calls copy
    }
}

int main() {
    try {
        Foo(true);
    } catch (const A& a) {
        std::cout << "caught in main! &a=" << &a << '\n';
    }
}
