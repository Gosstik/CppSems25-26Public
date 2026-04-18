#include <type_traits>

// NOLINTBEGIN(readability-identifier-naming)

template <typename T>
T&& forward(std::remove_reference_t<T>& x) noexcept {
    return static_cast<T&&>(x);
}

template <typename T>
T&& forward(std::remove_reference_t<T>&& x) noexcept {
    static_assert(!std::is_lvalue_reference_v<T>);
    return static_cast<T&&>(x);
}

// NOLINTEND(readability-identifier-naming)

////////////////////////////////////////////////////////////////////////////////

void Lvalue(int&) {}
void Rvalue(int&&) {}

int main() {
    int x = 1;

    Rvalue(forward<int>(x));   // OK
    Lvalue(forward<int&>(x));  // OK

    Rvalue(forward<int>(1));   // OK
    Lvalue(forward<int&>(1));  // CE
}
