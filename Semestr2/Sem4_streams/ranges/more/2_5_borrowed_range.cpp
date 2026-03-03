#include <iostream>
#include <vector>

// rng::sort returns rng::borrowed_iterator_t<R>

// concept borrowed_range = range<R> && (is_lvalue_ref_v<R> ||
// rng::enable_borrowed_range<remove_cvref_t<R>>)

// !!! enable_borrowed_range can be specialized to be true
// e.g. for std::string_view, std::span

namespace rng = std::ranges;

struct S {
    std::vector<int> Foo(size_t count) { return std::vector<int>(count); }
};

int main() {
    std::vector<int> v;
    auto res = rng::find(Foo(10), 21);
    auto elem = *res;  // CE thanks to borrowed_iterator_t and rng::dangling

    S s;
    for (auto val : s.Foo(10)) {  // OK
        std::cout << val << '\n';
    }

    for (auto val : S().Foo(10)) {  // UB until c++23
        std::cout << val << '\n';
    }
}
