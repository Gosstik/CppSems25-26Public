template <auto N>
struct Example {};

// template <typename T, T N>
// struct Example {};

int main() {
    Example<2> ei;
    Example<'a'> ec;
}
