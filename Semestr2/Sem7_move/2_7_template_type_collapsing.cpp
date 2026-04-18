#include <type_traits>
#include <utility>

// Reference collapsing rule
// &  + &  -> &
// &  + && -> &
// && + &  -> &
// && + && -> &&

// T is lvalue => T = T&
// T is rvalue => T = T
template <typename T>
void Foo(T&&) {  // 1
    static_assert(std::is_same_v<T, int> || std::is_same_v<T, int&>);
}

template <typename T>
void Bar(T&) {  // 2
    static_assert(std::is_same_v<T, int>);
}

template <typename T>
void Baz(T) {  // 3
    static_assert(std::is_same_v<T, int>);
}

int main() {
    int x = 1;
    Foo(x);  // T = int&
    Bar(x);  // T = int
    Baz(x);  // T = int

    int& y = x;
    Foo(y);  // T = int&
    Bar(y);  // T = int
    Baz(y);  // T = int

    int&& z = std::move(x);
    Foo(z);  // T = int&
    Bar(z);  // T = int
    Baz(z);  // T = int

    Foo(1);  // T = int
    // Bar(1);
    Baz(1);  // T = int
}
