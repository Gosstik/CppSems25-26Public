#include <iostream>

class Class {
    /* ... */
};

void Foo(const Class** p) { std::cout << "Foo\n"; }
void Bar(const Class* const* p) { std::cout << "Bar\n"; }

int main() {
    Class** p;

    Foo(p);  // ???
    Bar(p);  // ???
}
