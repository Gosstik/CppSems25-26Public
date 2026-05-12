#include <iostream>
#include <type_traits>

template <typename T>
auto CallFoo(const T& t) {  // Not SFINAE friendly
    return t.Foo();
}

// template <typename T>
// auto CallFoo(const T& t) -> decltype(t.Foo()) {  // SFINAE friendly
//   return t.Foo();
// }

////////////////////////////////////////////////////////////////////////////////

namespace detail {

template <typename T>
auto CallFooIfAvailableImpl(const T& t, int) -> decltype(CallFoo(t)) {
    return CallFoo(t);
}

template <typename T>
auto CallFooIfAvailableImpl(const T& t, ...) {
    // Do nothing
}

}  // namespace detail

template <typename T>
auto CallFooIfAvailable(const T& t) {
    return detail::CallFooIfAvailableImpl(t, 0);
}

////////////////////////////////////////////////////////////////////////////////

struct WithoutFoo {};
struct WithFoo {
    void Foo() const {  // NOLINT
        std::cout << "Foo called\n";
    }
};

int main() {
    std::cout << "Without Foo:\n";
    CallFooIfAvailable(WithoutFoo{});
    std::cout << "With Foo:\n";
    CallFooIfAvailable(WithFoo{});
}
