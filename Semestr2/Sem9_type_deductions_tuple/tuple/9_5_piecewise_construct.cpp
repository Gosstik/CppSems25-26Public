#include <iostream>
#include <type_traits>
#include <unordered_map>
#include <utility>

// https://en.cppreference.com/w/cpp/utility/piecewise_construct

// In short: create pair<tuple, tuple> from range of args
// pair ctors:
// https://en.cppreference.com/w/cpp/utility/pair/pair

// In map.emplace (see example):
// https://en.cppreference.com/w/cpp/container/map/emplace

#include <iostream>
#include <tuple>
#include <utility>

template <typename T, typename U>
struct Pair {
    Pair(const T& t, const U& u) : first(t), second(u) {}

    // Task: implement ctor of pair that can construct elements inplace
    // (copy and move ctors of T and U may be deleted)
    template <typename... Ts, typename... Us>
    Pair(std::piecewise_construct_t, std::tuple<Ts...> t1, std::tuple<Us...> t2)
        : Pair(
              std::piecewise_construct,
              t1,
              t2,
              std::make_index_sequence<sizeof...(Ts)>(),
              std::make_index_sequence<sizeof...(Us)>()) {}

    T first;
    U second;

  private:
    template <typename... Ts, typename... Us, size_t... Ids1, size_t... Ids2>
    Pair(
        std::piecewise_construct_t,
        std::tuple<Ts...>& t1,
        std::tuple<Us...>& t2,
        std::index_sequence<Ids1...>,
        std::index_sequence<Ids2...>)
        : first(std::forward<Ts>(std::get<Ids1>(t1))...),
          second(std::forward<Us>(std::get<Ids2>(t2))...) {}
};

////////////////////////////////////////////////////////////////////////////////

struct Foo {
    Foo(std::tuple<int, float>) {
        std::cout << "Constructed a Foo from a tuple\n";
    }

    Foo(int, float) {
        std::cout << "Constructed a Foo from an int and a float\n";
    }
};

int main() {
    std::tuple<int, float> t(1, 3.14);

    std::cout << "Creating p1...\n";
    std::pair<Foo, Foo> p1(t, t);

    std::cout << "Creating p2...\n";
    // std::pair<Foo, Foo> p2(
    //     std::piecewise_construct, t, t
    // );  // try to implement !!!

    Pair<Foo, Foo> p3(std::piecewise_construct, t, t);
}
