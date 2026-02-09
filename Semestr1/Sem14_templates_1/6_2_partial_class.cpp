#include <iostream>

template <typename T, typename U>
struct A {};

// Partial Specialization
template <typename V>
struct A<int, V> {};

template <typename V>
struct A<V, int> {};

// Full Specialization
template <>
struct A<int, int> {};

int main() {
    A<int, int> s;  // OK, but CE without Full specialization
}
