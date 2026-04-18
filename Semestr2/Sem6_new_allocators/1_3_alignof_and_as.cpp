#include <iostream>

// operator alignof
// https://en.cppreference.com/w/cpp/language/alignof

// operator alignas
// https://en.cppreference.com/w/cpp/language/alignas

template <typename T>
struct S {
    // char custom[sizeof(T)]{};
    alignas(T) char custom[sizeof(T)]{};
    // alignas(8) char custom[sizeof(T)]{};
    int x = 1;
    char c = 'c';

    explicit S(const T& t) { new (custom) T(t); }
};

static_assert(alignof(S<int>) == 4);     // OK
static_assert(alignof(S<double>) == 8);  // CE without alignas(T)

int main() {
    std::cout << "alignof(S<int>)=" << alignof(S<int>) << '\n';

    S<double> sd(3.14);
    std::cout << "sd.custom=" << sd.custom << '\n';
}
