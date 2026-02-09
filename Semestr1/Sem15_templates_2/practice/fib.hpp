#include <iostream>

// 'const' may be replaced by 'constexpr'

template <int N>
struct Fibonacci {
    static const int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template <>
struct Fibonacci<1> {
    static const int value = 1;
};

template <>
struct Fibonacci<0> {
    static const int value = 0;
};

void TestFib() { std::cout << Fibonacci<20>::value << '\n'; }
