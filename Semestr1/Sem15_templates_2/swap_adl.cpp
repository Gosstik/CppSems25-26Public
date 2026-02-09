// TODO: move to other section
#include <algorithm>
#include <iostream>

// !!! Skip that file

namespace impl {

struct BigInteger {
    friend void swap(BigInteger&, BigInteger&) {
        std::cout << "BigInteger::swap\n";
    }
};

}  // namespace impl

namespace my_std {

template <typename T>
void swap(T&, T&) {
    std::cout << "my_std::swap<T>\n";
}

template <>
void swap<impl::BigInteger>(impl::BigInteger&, impl::BigInteger&) {
    std::cout << "my_std::swap<impl::BigInteger>\n";
}

}  // namespace my_std

////////////////////////////////////////////////////////////////////////////////

namespace my_std {

void algo() {  // NOLINT
    impl::BigInteger a, b;
    swap(a, b);  // BigInteger::swap
    // ::swap(a, b);  // CE
    my_std::swap(a, b);  // my_std::swap<impl::BigInteger>
}

}  // namespace my_std

int main() { my_std::algo(); }
