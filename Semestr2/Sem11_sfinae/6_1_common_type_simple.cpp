#include <type_traits>

// common_type before c++17 (simple impl with :?)

//// Why that implementation is not SFINAE friendly?
// https://en.cppreference.com/w/cpp/types/common_type#Defect_reports

template <typename... Types>
struct common_type;

template <typename... Types>
using common_type_t = typename common_type<Types...>::type;

template <typename T, typename U>
struct common_type<T, U> {
    using type =
        std::decay_t<decltype(false ? std::declval<T>() : std::declval<U>())>;
};

template <typename T, typename U, typename... Types>
struct common_type<T, U, Types...>
    : common_type<common_type_t<T, U>, Types...> {};

struct Granny {};
struct Mom : Granny {};
struct Dad : Granny {};
struct Son : Mom, Dad {};

void Foo() {
    common_type_t<Mom, Granny> a;       // OK
    common_type_t<Granny, Mom, Dad> b;  // OK
    // common_type_t<Mom, Dad, Granny> c;  // CE, Granny should be first
}

////////////////////////////////////////////////////////////////////////////////

// Test SFINAE friendliness

template <typename T>
void Foo(T x, common_type_t<T, int> z) {}  // v1

template <typename...>
void Foo(...) {}  // v2

template <typename T>
void Bar(T x, std::common_type_t<T, int> z) {}  // v1

template <typename...>
void Bar(...) {}  // v2

int main() {
    Foo(1ull, 0);  // OK, simple conversion
    // Foo("abc", 0);  // CE, but expect to call v2 with SFINAE
    Bar("abc", 0);  // OK, std::common_type
}
