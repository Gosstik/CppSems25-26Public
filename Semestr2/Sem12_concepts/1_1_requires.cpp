#include <iostream>
#include <type_traits>

// requires specifier (requires clause) (since c++20)

// Comment Bar v2 and see compiler error

// Pay attention to equal signatures of Bar

// requires is strongly better than std::enable_if

// requires is a hook in name lookup

template <typename T, std::enable_if_t<std::is_class_v<T>, bool> = true>
void Foo(const T&) {
    std::cout << 1 << '\n';
}

template <typename T, std::enable_if_t<!std::is_class_v<T>, bool> = true>
void Foo(T) {
    std::cout << 2 << '\n';
}

////////////////////////////////////////////////////////////////////////////////

// "requires std::is_class_v<T>" is requires clause
// "std::is_class_v<T>" is constraint
template <typename T>
    requires std::is_class_v<T>
void Bar(const T&) {
    std::cout << 1 << '\n';
}

//// requires clause may be after function declaration
// template <typename T>
// void Bar(const T&)
//   requires std::is_class_v<T>
// {
//   std::cout << 1 << '\n';
// }

template <typename T>
    requires(!std::is_class_v<T>)  // parenthesis are required in case ! is used
void Bar(T) {
    std::cout << 2 << '\n';
}

template <typename T>
class Boo {
    // !!! Differet behaviour compared to std::enable_if
    void Foo()
        requires std::is_class<T>::value
    {}
};

////////////////////////////////////////////////////////////////////////////////

struct A {};

int main() {
    Foo(A{});    // 1
    Foo(int{});  // 2

    Bar(A{});    // 1
    Bar(int{});  // 2
}
