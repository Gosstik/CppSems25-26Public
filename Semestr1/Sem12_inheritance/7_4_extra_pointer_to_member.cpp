#include <iostream>

// sizeof(ptr to member) == 16

// Method calling:
// 1) Get the memory address of object
// 2) Apply implicit conversions. If the pointer-to-member type doesn't match the object type exactly,
//    the compiler performs implicit pointer conversions (like Son* -> Dad*), which may adjust the pointer
// 3) Add the stored offset from pointer-to-member
// 4) Call method

struct Granny {
    void Foo() { // NOLINT
        std::cout << "Granny::Foo\n";
    }
};
struct Mom : Granny {
    void Foo() { // NOLINT
        std::cout << "Mom::Foo\n";
    }
};
struct Dad : Granny {
    void Foo() { // NOLINT
        std::cout << "Dad::Foo\n";
    }
};
struct Son : Mom, Dad {
    void Foo() { // NOLINT
        std::cout << "Son::Foo\n";
    }
};

int main() {
    Son s;

    void (Son::* sp)() = &Son::Foo;

    sp = &Mom::Foo; // OK
    (s.*sp)(); // Mom::Foo

    sp = &Dad::Foo; // OK
    (s.*sp)(); // Dad::Foo

    // sp = &Granny::Foo; // CE

    std::cout << "--------------------\n";

    void (Dad::* dp)() = &Dad::Foo;

    // dp = &Son::Foo; // !!! CE
    (s.*dp)(); // OK, Dad::Foo

    dp = &Granny::Foo; // OK
    (s.*dp)(); // Granny::Foo

    std::cout << "--------------------\n";

    // Here offset != 0
    void (Son::* spd)() = &Dad::Foo; // !!! OK
    (s.*spd)(); // !!! OK, Dad::Foo

    std::cout << "--------------------\n";

    std::cout << "sizeof(mp) = " << sizeof(sp) << '\n'; // 16
}
