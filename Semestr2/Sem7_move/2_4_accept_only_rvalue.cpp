#include <type_traits>
#include <utility>

template <typename T>
void Foo(T&&) {}

template <typename T>
void Foo(T&) = delete;

template <typename T>
void Bar(T) {
    static_assert(std::is_same_v<T, std::remove_cvref_t<T>>);
}

template <typename T>
void Debug() = delete;

template <typename T>
void Baz(T& x) {
    // static_assert(std::is_same_v<T, std::remove_cvref_t<T>>);
    static_assert(std::is_same_v<T, std::remove_reference_t<T>>);
    // Debug<T>();
}

template <typename T>
void Baz2(const T) {
    static_assert(std::is_same_v<T, std::remove_cvref_t<T>>);
}

int main() {
    int x = 1;

    // Foo(x);  // CE
    Foo(1);  // OK

    const int y = 2;

    Bar(x);             // OK
    Bar(y);             // OK
    Bar(1);             // OK
    Bar(std::move(y));  // OK

    Baz(x);  // OK
    Baz(y);  // OK

    Baz2(x);  // OK
    Baz2(y);  // OK
}
