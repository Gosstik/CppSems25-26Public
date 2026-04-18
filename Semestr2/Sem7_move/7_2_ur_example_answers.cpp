#include <iostream>

// Universal references

// Actual problem for shared_ptr --- we have to write copy ctor from non const
// shared_ptr manually

template <typename T>
class A {
  public:
    A() = default;

    A(const A&) { std::cout << "1\n"; }

    template <typename U>
    A(A<U>&&) {
        std::cout << "2\n";
    }

    template <typename U>
    A(A<U>&) {
        std::cout << "3\n";
    }

    template <typename Other>
    A(Other&&) {
        std::cout << "4\n";
    }
};

int main() {
    A<int> a;
    A<int> b(a);                //* 4 3
    A<int> c(std::move(a));     //* 2 2
    A<double> d(a);             //* 4 3
    A<double> e(std::move(a));  //* 2 2
}
