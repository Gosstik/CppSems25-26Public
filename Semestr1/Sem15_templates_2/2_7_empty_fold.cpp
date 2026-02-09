#include <iostream>
#include <type_traits>

// NOLINTBEGIN(readability-identifier-naming)

// https://en.cppreference.com/w/cpp/language/fold

////////////////////////////////////////////////////////////////////////////////

template <typename... Types>
struct AllPointers {
    static const bool value = (std::is_pointer_v<Types> && ...);
};

template <typename... Types>
constexpr bool all_pointers_v = AllPointers<Types...>::value;

////////////////////////////////////////////////////////////////////////////////

template <typename... Types>
struct AnyPointer {
    static const bool value = (std::is_pointer_v<Types> || ...);
};

template <typename... Types>
constexpr bool any_pointer_v = AnyPointer<Types...>::value;

////////////////////////////////////////////////////////////////////////////////

template <typename... Args>
void Print(const Args&... args) {
    (void)(std::cout << ... << args);
    // ((std::cout << args << '\n'), ...);
}

////////////////////////////////////////////////////////////////////////////////

template <typename... Args>
int SumAll(Args... args) {
    return (args + ...);  // CE if sizeof...(args) == 0
    // return (0 + ... + args); // OK if sizeof...(args) == 0
}

int main() {
    static_assert(all_pointers_v<>);  // x && true = x
    static_assert(!any_pointer_v<>);  // x || false = x
    Print();                          // OK

    SumAll();
}

// NOLINTEND(readability-identifier-naming)
