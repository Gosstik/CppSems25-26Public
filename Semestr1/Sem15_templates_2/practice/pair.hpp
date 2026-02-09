#pragma once

// pair<T, U>
// copy
// make_pair ??? Make specialization for variadic types
// template method outside the class

#include <iostream>

template <typename T, typename U>
struct Pair {
    // template <typename T1, typename U1>
    // Pair(T1 first, U1 second) : first(first), second(second) {}

    Pair(T first, U second) : first(first), second(second) {}

    T first;
    U second;
};

template <typename... Args>
struct MyType {};

template <typename... Ts, typename... Us>
struct Pair<MyType<Ts...>, MyType<Us...>> {
    Pair(MyType<Ts...> first, MyType<Us...> second)
        : first(first),
          second(second) {}

    MyType<Ts...> first;
    MyType<Us...> second;
};

////////////////////////////////////////////////////////////////////////////////

void TestPair() {
    Pair pr(1, 2.0);
    std::cout << pr.first << '\n';
}
