#include <iostream>
#include <type_traits>

template <typename T>
void f(T x) {}

template <typename T>
void rf(T& x) {}

template <typename T>
void crf(const T& x) {}

template <typename T>
void tf(T&& x) {}

//////////////////////////////

template <typename T>
auto RetAuto(T x) {
    return ++x;
}

template <typename T>
auto& RetAutoRef(T x) {
    return ++x;
}

// Type conversion does not work for deduction
auto inconsistent_deduction(int x) {
    if (x > 0) {
        return 1;
    }
    return 1u;
}

template <typename T>
auto constexpr_g1(T x) {
    if constexpr (std::is_same_v<T, int>) {
        return 1;
    } else {
        return 1u;
    }
}

template <typename T>
auto constexpr_g2(T x) {
    if constexpr (std::is_same_v<T, int>) {
        return 1;
    }
    return 1u;  // CE
}

template <typename T>
auto recursion(T x) {
    if constexpr (std::is_same_v<T, int>) {
        return recursion(x);  // CE
    } else {
        return 1u;
    }
}

////////////////////////////////////

void arg_f(auto x) {}

void args_f(auto... x) {}

////////////////////////////////////

template <auto N>
struct Example {};

////////////////////////////////////

// initializer list
template <typename T>
void h(T) {}

int main() {
    {
        auto x = 5;
        auto& rx = x;
        const auto& crx = x;
        auto&& t = x;              // as universal reference
        auto&& t2 = std::move(x);  // as universal reference
    }

    {
        auto&& x1 = RetAuto(1);
        auto&& x2 = RetAutoRef(1);  // UB
    }

    {
        constexpr_g1<int>(1);
        constexpr_g1<double>(2.0);

        constexpr_g2<int>(1);
        constexpr_g2<double>(2.0);

        recursion(1);
    }

    {
        h({1, 2, 3});          // CE
        auto lst = {1, 2, 3};  // OK
    }
}
