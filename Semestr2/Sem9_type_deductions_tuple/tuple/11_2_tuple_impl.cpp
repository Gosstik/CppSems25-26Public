#include <iostream>

// TODO: ctors are conditionally explicit (since c++20)
// TODO: several ctors participate in overload resolution by condition
// with enable_if (see usage) or concepts

// NOLINTBEGIN(readability-identifier-naming)

//// Option 1, elements are initialized in reserve order
// template <typename Head, typename... Tail>
// struct tuple: tuple<Tail...> {
//  Head head;
// };

// Option 2
template <typename... Args>
class tuple;

template <typename Head, typename... Tail>
class tuple<Head, Tail...> {
  private:
    Head head;
    tuple<Tail...> tail;

    template <size_t N, typename... Types>
    friend decltype(auto) get(tuple<Types...>&);
};

template <>
class tuple<> {};  // Without EBO

////////////////////////////////////////////////////////////////////////////////

// get

// TODO: invalid implementation, write 4 versions instead
// (for (const) && forward must be used, for (const) & no forward is used)
template <size_t N, typename... Types>
decltype(auto) get(tuple<Types...>& t) {
    if constexpr (N == 0) {
        return t.head;
    } else {
        return get<N - 1>(t.tail);
    }
}

////////////////////////////////////////////////////////////////////////////////

// tuple_cat

// TODO: avoid too much copies

struct tuple_cat_tag {};

template <typename... Us>
auto tuple_cat(tuple<> t, tuple<Us...>& u) {
    return u;
}

template <typename... Ts, typename... Us>
auto tuple_cat(tuple<Ts...>& t, tuple<Us...>& u) {
    return tuple(tuple_cat_tag{}, t.head, tuple_cat(t.tail, u));
}

////////////////////////////////////////////////////////////////////////////////

// NOLINTEND(readability-identifier-naming)

int main() {}
