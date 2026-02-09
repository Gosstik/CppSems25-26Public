#include <iomanip>
#include <iostream>

struct Base {
    void Foo() const { std::cout << x << '\n'; }

    bool x = false;
};

struct Derived : Base {
    void Foo() const { std::cout << y << '\n'; }

    bool y = true;
};

int main() {
    std::cout << std::boolalpha;

    {
        Derived d;
        Base& b = d;

        auto dd = dynamic_cast<Derived&>(b);  // CE
        auto sd = static_cast<Derived&>(b);   // OK

        dd.Foo();
        sd.Foo();
    }

    {
        // !!! dynamic_cast Derived -> Base works even for non-polymorphic types
        Derived d;
        Base b = dynamic_cast<Derived&>(d);
    }
}
