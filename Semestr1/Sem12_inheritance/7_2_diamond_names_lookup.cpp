#include <iostream>

// Name lookup does not depend on inheritance type !!!
// Same with class members

// Try Mom: virtual Granny, Dad: virtual Granny

struct Granny {
    void Foo() { // NOLINT
        std::cout << "Granny::Foo\n";
    }
};

struct Mom : Granny {
    // void Foo() { // NOLINT
    //     std::cout << "Mom::Foo\n";
    // }
};

// struct Dad : Granny {};
struct Dad : private Granny {};

struct Son : Mom, Dad {
    // void Foo() { // NOLINT
    //     std::cout << "Son::Foo\n";
    // }
};

int main() {
    Son s;

    s.Foo();
    s.Mom::Foo();
    s.Granny::Foo(); // CE
    s.Mom::Granny::Foo(); // !!! Always CE

    // Mom& m = s;
    // m.Granny::Foo();
}
