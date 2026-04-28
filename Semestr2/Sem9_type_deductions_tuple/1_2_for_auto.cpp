#include <utility>

template <typename T>
void GetIterable(T&& c) {
    // wrapper that returns move_range or range conditionally
}

template <typename Container>
void Foo(Container&& c) {
    // mostly like you will want to use auto&& to support types
    // such as vector<bool>

    // for (auto it = c.begin(); it != c.end(); ++it) {
    //     auto& val = *it;
    // }
    for (auto&& val : c) {
        // fail for vector<bool>
    }

    for (auto&& val : std::forward<Container>(c)) {
        // requires ref qualifiers support in c.begin() and c.end()
        // ...
    }

    // More likely
    for (auto&& val : GetIterable(std::forward<Container>(c))) {
        // requires ref qualifiers support in c.begin() and c.end()
        // ...
    }
}
