#include <string>
#include <type_traits>

// !!! noexcept(noexcept(T(std::move(lhz)))) doesn't work here

// std::is_nothrow_swappable_v<T>

void Foo() {}

template <typename T>
void Swap(T& lhz, T& rhs) noexcept(
    std::is_nothrow_move_constructible_v<T> &&
    std::is_nothrow_move_assignable_v<T>) {
    T tmp = std::move(lhz);  // what if type does not have move ctor ???
    lhz = std::move(rhs);
    rhs = std::move(tmp);
}

struct S {
    std::string str;
};

int main() {
    S s1;
    S s2;
    std::swap(s1, s2);  // standard implementation
}
