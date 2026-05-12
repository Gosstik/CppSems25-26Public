#include <type_traits>

// NOLINTBEGIN(readability-identifier-naming)

// Problem occurs when we try to make several specializations (dispatching)

template <typename...>
using void_t = void;

template <typename...>
struct smart_void : std::type_identity<void> {};

template <typename... Args>
using smart_void_t = smart_void<Args...>::type;

////////////////////////////////////////////////////////////////////////////////

//// void_t

template <typename T, void_t<typename T::First>* = nullptr>
int Foo() {
    return 1;
}

// An alias template that does not depend on its arguments on the right side
// is resolved by the compiler immediately when comparing function signatures.
template <typename T, void_t<typename T::Second>* = nullptr>
int Foo() {
    return 2;
}

////////////////////////////////////////////////////////////////////////////////

//// smart_void_t

template <typename T, smart_void_t<typename T::First>* = nullptr>
int SmartFoo() {
    return 1;
}

// With structs that optimization does not work because someone can potentially
// make specislization for struct template, for example.
template <typename T, smart_void_t<typename T::Second>* = nullptr>
int SmartFoo() {
    return 2;
}

////////////////////////////////////////////////////////////////////////////////

//// Fix without smart_void_t

template <typename T, std::type_identity<typename T::First>* = nullptr>
int FixFoo() {
    return 1;
}

template <typename T, std::type_identity<typename T::Second>* = nullptr>
int FixFoo() {
    return 2;
}

////////////////////////////////////////////////////////////////////////////////

//// Tests

struct One {
    using First = int;
};

struct Two {
    using Second = int;
};

int main() {
    auto i1 = Foo<One>();  // CE
    auto i2 = Foo<Two>();  // CE

    auto j1 = SmartFoo<One>();  // OK
    auto j2 = SmartFoo<Two>();  // OK

    auto k1 = FixFoo<One>();  // OK
    auto k2 = FixFoo<Two>();  // OK
}

// NOLINTEND(readability-identifier-naming)
