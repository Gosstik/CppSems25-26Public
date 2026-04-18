//* Without explicit <> forward can move

template <typename T>
T&& forward(T& x) {  // NOLINT(readability-identifier-naming)
    return static_cast<T&&>(x);
}

////////////////////////////////////////////////////////////////////////////////

void Lvalue(int&) {}
void Rvalue(int&&) {}

int main() {
    int x = 1;

    // Rvalue(forward<int>(x));   // 1
    // Lvalue(forward<int&>(x));  // 2

    // Rvalue(forward<int>(1));   // 3
    // Lvalue(forward<int&>(1));  // 4
}
