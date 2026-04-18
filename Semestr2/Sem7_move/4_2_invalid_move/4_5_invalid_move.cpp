#include <type_traits>

// NOLINTBEGIN(readability-identifier-naming)

template <typename T>
std::remove_reference_t<T> move(T&& x) {
    return static_cast<std::remove_reference_t<T>&&>(x);
}

// NOLINTEND(readability-identifier-naming)

////////////////////////////////////////////////////////////////////////////////

void Rvalue(int&&) {}

int main() {
    int x = 1;

    // Rvalue(move(x));        // 1
    // Rvalue(move(1));        // 2
    // Rvalue(move<int&>(x));  // 3
}
