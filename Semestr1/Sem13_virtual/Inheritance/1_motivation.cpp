#include <iostream>

// Motivation: solve diamond problem (avoid parents duplication)

struct Granny {
    void Foo() {  // NOLINT
        std::cout << "Granny::Foo\n";
    }
    int g;
};

struct Mom : virtual Granny {  // NOLINT
    int m;
};

struct Dad : virtual Granny {  // NOLINT
    int d;
};

struct Son : Mom, Dad {  // NOLINT
    int s;
};

int main() {
    std::cout << sizeof(Son) << '\n'; //

    // Calls
    Son s;
    s.Foo();               // OK
    s.Mom::Foo();          // OK
    s.Granny::Foo();       // OK
    s.Mom::Granny::Foo();  // OK

    // Casts
    Granny& g1 = static_cast<Granny&>(s); // OK
    Son& s1 = static_cast<Son&>(g1); // !!! CE, ambiguity is possible

}
