#include <iostream>

template <typename T, typename I>
struct Main {
    template <typename V>
    struct Inner {
        template <typename U>
        void Foo();
    };
};

template <typename T, typename I>
template <typename V>
template <typename U>
void Main<T, I>::Inner<V>::Foo() {}

int main() {}
