#include <iostream>
#include <type_traits>

template <typename T>
auto RetAuto(T) {
    if constexpr (std::is_same_v<T, int>) {
        return 1;
    } else {
        return 1u;
    }
}

template <typename T>
auto Bar(T) {
    if constexpr (std::is_same_v<T, int>) {
        return 1;
    }
    return 1u;  // CE
}

int main() {
    RetAuto<int>(1);
    RetAuto<double>(2.0);

    Bar<int>(1);  // try to comment it
    Bar<double>(2.0);
}
