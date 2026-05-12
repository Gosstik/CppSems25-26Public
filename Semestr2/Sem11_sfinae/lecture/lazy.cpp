#include <iostream>

// Причина lazy инстанцирования: Избежание лавинообразного инстанцирования
// (уменьшение размера бинарника и времени компиляции)

template <int N>
struct Danger {
    using Block = char[N];
};

template <typename T, int N>
struct Tricky {
    int k = N;
    void TestLazyness() { Danger<N> no_boom_yet; }

    void StupidTestLazyness() {
        Danger<N> no_boom_yet;
        / +1;  // CE in any case
    }
};

int main() {
    Tricky<int, -2> ok;
    // OK, because TestLazyness actually may be associated as template function
    // (T is template parameter for this)
    std::cout << (ok.k == -2) << std::endl;
}
