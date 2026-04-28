#include <type_traits>

template <typename T>
auto RetAuto(T x) {
    if constexpr (std::is_same_v<T, int>) {
        return RetAuto(x);  // CE
    } else {
        return 1u;
    }
}

int main() { RetAuto(1); }
