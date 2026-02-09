#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// RunTime Type Information

// https://en.cppreference.com/w/cpp/types/type_info

// c++filt -t <mangled_name>

namespace impl {

struct Base {
    virtual void Foo() const { std::cout << x << '\n'; }

    virtual ~Base() = default;

    int x = 0;
};

struct Derived : Base {
    void Foo() const override { std::cout << y << '\n'; }

    int y = 1;
};

}  // namespace impl

using namespace impl;

struct S {};

int main() {
    std::cout << std::boolalpha;

    {
        Derived d;
        Base* b = &d;

        std::cout << typeid(d).name() << '\n';
        std::cout << typeid(b).name() << '\n';
        std::cout << typeid(*b).name() << '\n';
    }

    {
        // primitive types
        int a = 1;
        double d = 2.0;
        char c = 'c';
        unsigned long long y = 10;

        std::cout << typeid(a).name() << '\n';
        std::cout << typeid(d).name() << '\n';
        std::cout << typeid(c).name() << '\n';
        std::cout << typeid(y).name() << '\n';
    }

    {
        std::cout << typeid(std::cout).name() << '\n';
        std::cout << typeid(std::cin).name() << '\n';
        std::cout << typeid(std::string::npos).name() << '\n';
        std::cout << typeid(std::vector<int>{}.begin()).name() << '\n';
    }

    {
        Derived d;
        Base& b = d;

        // std::type_info ti = typeid(d); // CE: deleted ctor
        const std::type_info& tid = typeid(d);
        const std::type_info& tib = typeid(b);

        std::cout << tid.name() << '\n';
        std::cout << tid.hash_code() << '\n';

        std::cout << (tid == tib) << '\n';
    }
}
