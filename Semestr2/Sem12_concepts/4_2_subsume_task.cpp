#include <iostream>

template <typename T>
void Foo(T val)
    requires(sizeof(T) < 8)
{
    std::cout << "Less than 8\n";
}

template <typename T>
void Foo(T val)
    requires(sizeof(T) <= 4)
{
    std::cout << "Less than 4\n";
}

int main() {
    // Foo(int32_t(1)); // ???
}
