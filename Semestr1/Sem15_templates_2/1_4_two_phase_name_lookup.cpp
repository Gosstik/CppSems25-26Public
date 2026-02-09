#include <iostream>

// lazy behaviour

// https://en.cppreference.com/w/cpp/language/two-phase_lookup.html

template <typename T>
struct S {
    explicit S(T x) : x(x) {}

    int GetIllegalNameValue() {
        // +-+;
        // return illegal_name; // CE, independent name
        // return T::illegal_name; // OK, dependent name
        return this->illegal_name;  // OK, dependent name
    }

    T x;
    // int illegal_name = 42;
};

int main() {
    S s(1);
    std::cout << s.x << '\n';
    // std::cout << s.GetIllegalNameValue() << '\n';
}
