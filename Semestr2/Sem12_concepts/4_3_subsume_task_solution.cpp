#include <iostream>

// You can write "LessThan8 T" instead of "typename T", subsume also works

template <typename T>
concept LessThan8 = sizeof(T) < 8;

template <typename T>
void Foo(T val)
    requires LessThan8<T>
{
    std::cout << "Less than 8\n";
}

template <typename T>
void Foo(T val)
    requires(LessThan8<T> && sizeof(T) <= 4)
{
    std::cout << "Less than 4\n";
}

int main() {
    Foo(int32_t(1));  // OK
}
