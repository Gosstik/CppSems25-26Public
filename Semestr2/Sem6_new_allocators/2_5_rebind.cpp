// NOLINTBEGIN(readability-identifier-naming)

template <typename T>
struct MyAlloc {
    template <typename U>
    MyAlloc(const MyAlloc<U>) {}

    template <typename U>
    struct rebind {
        using other = MyAlloc<U>;
    };
};

// NOLINTEND(readability-identifier-naming)
