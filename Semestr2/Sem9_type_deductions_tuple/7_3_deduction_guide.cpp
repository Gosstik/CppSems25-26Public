#include <iostream>
#include <iterator>
#include <vector>

// CTAD --- Class Template Argument Deduction

template <typename T>
struct Vector {
    template <typename Iter>
    Vector(Iter, Iter) {
        // ...
    }
};

// Explicit template deduction guide (since c++17)
template <typename Iter>
Vector(Iter, Iter) -> Vector<typename std::iterator_traits<Iter>::value_type>;

// Create tuple<T, U> from pair<T, U>

// Deduction guides can be applied to usings (since c++20)

int main() {}
