#include <iostream>
#include <vector>

// Can be partially specialized: structures/classes and global variables
// Cannot be partially specialized: functions, aliases (using)

////////////////////////////////////////////////////////////////////////////////

// Struct

template <typename T>
struct A {
    T val;
};

template <typename T>
struct A<std::vector<T>> {
    T* begin;
    T* end;
};

////////////////////////////////////////////////////////////////////////////////

// Variable

template <typename T, typename U>
constexpr int kGlobal = sizeof(T) + sizeof(U);

template <typename T>
constexpr int kGlobal<T, int> = sizeof(T);

////////////////////////////////////////////////////////////////////////////////

// Functions

template <typename T>
void Func(T) {}

// template <typename T>
// void Func<T&>(T&) {}

////////////////////////////////////////////////////////////////////////////////

// Aliases

template <typename T>
using Alias = std::vector<T>;

// template <typename T>
// using Alias<T&> = std::vector<std::reference_wrapper<T>>;

////////////////////////////////////////////////////////////////////////////////

int main() {
    static_assert(kGlobal<double, double> == 16);
    static_assert(kGlobal<double, int> == 8);
}
