#include <concepts>
#include <iostream>
#include <type_traits>
#include <vector>

namespace detail {

template <typename T, typename U>
concept SameAsHelper = std::is_same_v<T, U>;

}  // namespace detail

template <typename T, typename U>
concept SameAs = detail::SameAsHelper<T, U> && detail::SameAsHelper<U, T>;

//// Does not work for lvalues
// template <SameAs<std::vector<int>> Vector>
// void Foo(Vector&& vec) {
//     std::cout << vec[0];
// }

//// Works for both lvalues and rvalues, produces universal reference
template <typename Vector>
    requires SameAs<std::remove_cvref_t<Vector>, std::vector<int>>
void Foo(Vector&& vec) {
    std::cout << vec[0];
}

int main() {
    std::vector<int> v;
    Foo(v);
    Foo(1);
}
