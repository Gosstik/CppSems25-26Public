#include <iostream>

// ABI

struct A {
    void Foo() {}
};

struct B {
    virtual void Foo() {}
};

// A::type_info, A::Foo()
// ptr points to A::Foo()

static_assert(sizeof(A) == 1);
static_assert(sizeof(B) == 8);
