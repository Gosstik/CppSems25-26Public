#include <iostream>

// Why get is outer function and not tuple method ???

template <typename... Types>
void Foo() {
    std::tuple<Types...> t;

    t.template get<1>();
}

int main() {}
