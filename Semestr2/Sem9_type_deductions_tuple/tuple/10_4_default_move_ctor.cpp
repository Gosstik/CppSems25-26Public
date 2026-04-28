#include <iostream>

// clang-format off

// Description of all std::tuple ctors:
// https://en.cppreference.com/w/cpp/utility/tuple/tuple.html

// (14) tuple( tuple&& other ) = default;

// Description:

// Implicitly-defined move constructor.
// For all i, initializes the ith element of the tuple with std::forward<Ui>(std::get<i>(other)).

// Why std::forward<> is used inside default move constructor ???
// See [class.copy.ctor]:
// (14): The implicitly-defined copy/move constructor for a non-union class X performs a memberwise copy/move of its bases and members.

// That means that for a defaulted move constructor:
// - Non-static data members of class type are move-constructed
// - Reference members are direct-initialized (for references that means static_cast<T&>(other.ref))

// clang-format on

struct S {
    S(int& a) : a(a) {}
    S(const S& other) : a(other.a) { std::cout << "S(const S&)\n"; }
    S(S&& other) = default;

    int& a;
};

int main() {
    int a = 1;
    S s1(a);
    S s2(std::move(s1));  // OK
}
