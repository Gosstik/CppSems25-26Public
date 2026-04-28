
// Will compile ???

template <typename T>
auto Foo(T x) {
    if (x > 0) {
        return 1;
    }
    return 1u;
}

int main() {
    // ...
}
