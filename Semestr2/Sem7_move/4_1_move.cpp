#include <type_traits>
#include <utility>

// Instead of move it is possible to write static_cast<T&&>
// std::move --- cast from lvalue to rvalue
// std::move does NOT produce processor instructions

// NOLINTBEGIN(readability-identifier-naming)

template <typename T>
std::remove_reference_t<T>&& move(T&& x) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(x);
}

//// Additional
// template <typename T>
// std::remove_reference_t<T>&& move(T& x) {
//   return static_cast<std::remove_reference_t<T>&&>(x);
// }

// NOLINTEND(readability-identifier-naming)

////////////////////////////////////////////////////////////////////////////////

void Foo(const int&) {}  // 1
void Foo(int&&) {}       // 2

void Bar(const int& val) {
    Foo(val);             // what version?
    Foo(std::move(val));  // what version?
}

////////////////////////////////////////////////////////////////////////////////

void Rvalue(int&&) {}

int main() {
    int x = 1;

    Rvalue(move(x));        // OK
    Rvalue(move(1));        // OK
    Rvalue(move<int&>(x));  // OK
    Rvalue(move<int>(x));   // CE, but may be implemented to be OK
}
