#include <iostream>

struct Mom {
    virtual void Foo() {  // NOLINT
        std::cout << 1 << '\n';
    }
};

struct Dad {
    void Foo() {  // NOLINT
        std::cout << 2 << '\n';
    }
};

struct Son : Mom, Dad {
    void Foo() override { std::cout << 3 << '\n'; }
};

int main() {
    Son s;

    Mom& ms = s;
    ms.Foo();  // ???

    Dad& ds = s;
    ds.Foo();  // ???
};
