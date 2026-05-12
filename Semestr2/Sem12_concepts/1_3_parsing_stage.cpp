#include <iostream>
#include <type_traits>

// Compiler is able to detect redefinition in case requires is identical and
// placed in the same place. That is because requires clauses are checked on
// the early stages of compilation.

////////////////////////////////////////////////////////////////////////////////

template <typename T>
    requires std::is_pointer_v<T>
void Foo() {
    std::cout << 1 << '\n';
}

template <typename T>
    requires std::is_pointer_v<T>
void Foo() {
    std::cout << 2 << '\n';
}

////////////////////////////////////////////////////////////////////////////////

// change requires place

template <typename T>
    requires std::is_pointer_v<T>
void Bar() {
    std::cout << 1 << '\n';
}

template <typename T>
void Bar()
    requires std::is_pointer_v<T>
{
    std::cout << 2 << '\n';
}

////////////////////////////////////////////////////////////////////////////////

// change _v with ::value

template <typename T>
    requires std::is_pointer_v<T>
void Baz() {
    std::cout << 1 << '\n';
}

template <typename T>
    requires std::is_pointer<T>::value
void Baz() {
    std::cout << 2 << '\n';
}

////////////////////////////////////////////////////////////////////////////////

int main() {
    // Baz<int*>();
}
