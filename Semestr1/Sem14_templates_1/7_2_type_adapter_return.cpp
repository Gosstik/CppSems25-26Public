#include <iostream>
#include <vector>

// Task: You are given function T Foo(U) that returns sizeof(U). You have to add
// specialization for T=bool: Foo(U) must return sizeof(U) < 8.

////////////////////////////////////////////////////////////////////////////////

//// Solution with auto

template <typename T, typename U>
struct A {
    static T FooImpl(U) { return sizeof(U); }
};

template <typename U>
struct A<bool, U> {
    static bool FooImpl(U) { return sizeof(U) < 8; }
};

template <typename T, typename U>
auto Foo(U a) {
    return A<T, U>::FooImpl(a);
}

////////////////////////////////////////////////////////////////////////////////

//// Solution with Type2Type

// template <typename T>
// struct Type2Type {
//   using Type = T;
// };

// template <typename T, typename U>
// T Foo(U, Type2Type<T>) {
//   return sizeof(U);
// }

// template <typename U>
// bool Foo(U, Type2Type<bool>) {
//   return sizeof(U) < 8;
// }

int main() {
    //// auto
    std::cout << Foo<int64_t>(int64_t{}) << '\n';  // 8
    std::cout << Foo<bool>(int64_t{}) << '\n';     // 0

    // //// Type2Type
    // std::cout << Foo(int64_t{}, Type2Type<int64_t>{}) << '\n';  // 8
    // std::cout << Foo(int64_t{}, Type2Type<bool>{}) << '\n';     // 0
}
