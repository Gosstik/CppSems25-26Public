#include <iostream>
#include <type_traits>

// !!! Compiler does not search for more specific constraint.
// All versions where requires clause evaluates to true participate in overload
// resolution.

////////////////////////////////////////////////////////////////////////////////

template <typename T>
    requires std::is_pointer_v<T> &&
             std::is_integral_v<std::remove_pointer_t<T>>
void Foo() {
    std::cout << 1 << '\n';
}

template <typename T>
    requires std::is_pointer_v<T>
void Foo() {
    std::cout << 2 << '\n';
}

////////////////////////////////////////////////////////////////////////////////

int main() {
    int* pi = nullptr;
    void* pv = nullptr;
    Foo<int*>();   // CE: ambiguous call
    Foo<void*>();  // 2
}
