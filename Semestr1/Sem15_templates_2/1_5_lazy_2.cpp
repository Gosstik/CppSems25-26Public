#include <iostream>

// Basic syntactic checks are made in any case
// Lazy instantiation helps to avoid instantiation of all units in std::

template <int N>
struct Danger {
    typedef char block[N];
};

template <typename T, int N>
struct Tricky {
    int k = N;
    void TestLazyness() { Danger<N> no_boom_yet; }
};

int main() {
    Tricky<int, -2> ok;
    std::cout << ok.k;
    // ok.TestLazyness(); // CE, but ok without calling
}
