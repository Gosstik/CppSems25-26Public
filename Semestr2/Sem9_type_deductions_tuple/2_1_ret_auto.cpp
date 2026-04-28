#include <iostream>
#include <type_traits>

template <typename T>
auto RetAuto(T x) {
    return ++x;
}

template <typename T>
auto& RetAutoRef(T x) {
    return ++x;
}

// int& Foo(int x) {
//     return ++x;
// }

int main() {
    {
        // auto& rx = RetAuto(1);  // CE
        auto&& rrx = RetAuto(1);
    }

    {
        auto& rx = RetAutoRef(1);  // UB
        auto&& rrx = RetAutoRef(1);  // !!! UB, not temporary materialization
    }
}
