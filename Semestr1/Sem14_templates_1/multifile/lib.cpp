#include "lib.hpp"

// Try to comment
// 1. Only b) --- linker error
// 2. Only a) --- explicit instantiation of undefined function template

// a)
template <typename T>
T Min(const T& a, const T& b) {
    return a < b ? a : b;
}

// b)
template int Min(const int& a, const int& b);
