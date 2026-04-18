#include <iostream>
#include <utility>

// Copy elision and rvo, guaranteed copy elision
// https://en.cppreference.com/w/cpp/language/copy_elision

struct A {
    A() : x(0) { std::cout << "A()\n"; }
    A(int x) : x(x) { std::cout << "A(int)\n"; }
    A(const A& other) : x(other.x) { std::cout << "A(copy)\n"; }
    A(A&& other) : x(other.x) { std::cout << "A(move)\n"; }
    ~A() { std::cout << "~A()\n"; }

    int x;
};

struct S {
    S(int x) : x(x) { std::cout << "S(int)\n"; }
    S(const S& other) : x(other.x) { std::cout << "S(copy)\n"; }
    S(S&& other) : x(other.x) { std::cout << "S(move)\n"; }
    ~S() { std::cout << "~S()\n"; }

    int x;
    A a;
};

S Foo0(S s) {
    return s;  //* move ctor is called
}

S Foo1(S& s) {
    return s;  // copy
}

S Foo2(S&& s) {
    return s;  // no copy even without move !!!
}

A GetA(S&& s) {
    return s.a;  // No move without explicit std::move
}

A GetAMove(S&& s) { return std::move(s.a); }

A GetAMoveTricky(S&& s) {
    A&& a = std::move(s.a);
    return a;
}

int main() {
    //// S(int) ~S()
    // S s1 = S(S(S(S(S(1)))));

    //// S(int) S(move) ~S() ~S()
    // S s2 = std::move(S(S(S(S(S(1)))))); // rvalue -> xvalue

    //// Will create S at least once even if result is unused
    // S(S(S(S(S(1)))));

    //// Accessing class members causes rvalue -> xvalue
    // S s3 = S(S(1).x); // calls S(int) twice

    //// Even if compiler cannot make RVO, it tries to call move ctor
    // S s4 = Foo(S(1));

    //// s is reference inside bar, without std::move there will be copy
    // S tmp(1);                     // S(int)
    // S s5 = Foo0(tmp);             // S(copy) + S(move)
    // S s6 = Foo1(tmp);             // S(copy)
    // S s7 = Foo2(std::move(tmp));  // S(move)

    //// case when std::move is reasonable in return statement
    // A a1 = GetA(std::move(S(1)));      // A() + S(int) + A(copy)
    // A a2 = GetAMove(std::move(S(1)));  // A() + S(int) + A(move)
    A a3 = GetAMoveTricky(std::move(S(1)));  // A() + S(int) + A(move)
}
