#include <iostream>

struct Granny {
    void Foo() { // NOLINT
        std::cout << "Granny::Foo\n";
    }

    int g;
};
struct Mom : Granny {
    void Foo() { // NOLINT
        std::cout << "Mom::Foo\n";
    }
};

// Granny is inaccessible base class
struct Son : Mom, Granny {
};

int main() {
    Son s;
    s.Granny::Foo(); // !!! CE
    std::cout << s.Granny::g << '\n'; // !!! CE
}
