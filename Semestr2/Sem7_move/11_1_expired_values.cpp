#include <string>
#include <utility>

// clang-format off

// 5 types of value categories:
// https://en.cppreference.com/w/cpp/language/value_category

//      glvalue    rvalue
//      |     |    |    |
// lvalue     xvalue    prvalue
//          (expired)   (pure)

// string s = string("abc"); // copy elision, string("abc") is rvalue
// string s = std::move(string("abc")); // no copy elision, xvalue
// since c++17 copy elision is guaranteed

// lvalue --- something, that has address
// glvalue --- something, that has address, but behaves as rvalue
// rvalue --- something without address (compiler is permitted not to create such objects)

// clang-format on

std::string Foo() {
    // temporary materialization --- conversion of prvalue to xvalue
    return std::move(std::string("abc"));
}

std::string Bar() {
    return std::string(std::string("abc"));  // copy elision
}

int main() {
    std::string s1(Foo()); // x2 move ctor
    std::string s2(Bar()); // x1 move ctor
}

// Implicit conversions:
// https://en.cppreference.com/w/cpp/language/implicit_conversion
// Specific about temporary materialization:
// https://en.cppreference.com/w/cpp/language/implicit_conversion#Temporary_materialization

// Lvalue-to-rvalue conversion
// https://en.cppreference.com/w/cpp/language/implicit_conversion#Lvalue-to-rvalue_conversion
// TODO: figure out
