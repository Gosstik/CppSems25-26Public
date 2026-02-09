#include <iomanip>
#include <iostream>

// Advantage of dynamic_cast over static_cast: it throws exception and make
// checks in runtime. static_cast will cause CE or UB.

// dynamic_cast casts only to ref or ptr, not objects (same as reinterpret_cast)

// clang++ -fsanitize=address,undefined 6_1_dynamic_cast.cpp

struct Base {
    virtual void Foo() const { std::cout << x << '\n'; }

    virtual ~Base() = default;

    int x = 0;
};

struct Derived : Base {
    void Foo() const override { std::cout << y << '\n'; }

    int y = 1;
};

struct SimpleBase {};
struct SimpleDerived : SimpleBase {};

int main() {
    std::cout << std::boolalpha;

    // !!! When type is polymorphic prefer dynamic_cast over static_cast

    {
        Derived d;
        Base& b = d;
        auto dd = dynamic_cast<Derived&>(b);  // OK
        auto sd = static_cast<Derived&>(b);   // OK

        dd.Foo();
        sd.Foo();
    }

    {
        Base b;
        Base* pb = &b;
        auto db = dynamic_cast<Derived*>(pb);  // nullptr
        auto sb = static_cast<Derived*>(pb);   // UB

        std::cout << (db == nullptr) << '\n';
        sb->Foo();
    }

    {
        Base b;
        Base& rb = b;
        auto db = dynamic_cast<Derived&>(rb);  // RE (throws exception)
        auto sb = static_cast<Derived&>(rb);   // UB

        sb.Foo();
    }

    {
        Derived d;
        Base* pb = &d;

        if (auto pd = dynamic_cast<Derived*>(pb); pd != nullptr) {
            pd->Foo();
        } else {
            std::cout << "dynamic_cast failed\n";
        }
    }

    {
        // dynamic_cast to void* works for all polymorphic types
        Derived d;
        Base* pb = &d;

        if (auto pv = dynamic_cast<void*>(pb); pv != nullptr) {
            std::cout << "dynamic_cast to void* works\n";
        }
    }
}
