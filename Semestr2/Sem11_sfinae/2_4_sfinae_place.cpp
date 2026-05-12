#include <iostream>
#include <vector>

//// Constraints on type for SFINAE must be located in:
// 1) template arguments
// 2) return type
// 3) function arguments

struct TemplateArgTag {};
struct ReturnTypeTag {};
struct FunctionArgTag {};
struct NotInSignatureTag {};

////////////////////////////////////////////////////////////////////////////////

template <typename... Args>
auto Foo(Args...) {
    std::cout << "fallback\n";
}

//// 1) template arguments
template <typename Container, typename = Container::size_type>
auto Foo(Container& c, TemplateArgTag) {
    std::cout << 1 << '\n';
    return c.size();
}

//// 2) return type
template <typename Container>
auto Foo(Container& c, ReturnTypeTag) -> typename Container::size_type {
    std::cout << 2 << '\n';
    return c.size();
}

//// 3) function arguments
template <typename Container>
auto Foo(
    Container& c,
    FunctionArgTag,
    std::void_t<typename Container::size_type>* /*unused*/ = nullptr) {
    std::cout << 3 << '\n';
    return c.size();
}

//// CE, value_type is not in signature
template <typename Container>
auto Foo(Container& c, NotInSignatureTag) {
    using Result = typename Container::size_type;

    std::cout << "signature" << '\n';
    Result res = c.size();
    return res;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
    int a = 1;
    Foo(a, TemplateArgTag{});  // OK, fallback
    Foo(a, ReturnTypeTag{});   // OK, fallback
    Foo(a, FunctionArgTag{});  // OK, fallback
    Foo(a, NotInSignatureTag{});  // CE

    std::vector<char> vec(3, 'a');

    Foo(vec, TemplateArgTag{});     // OK, 1
    Foo(vec, ReturnTypeTag{});      // OK, 2
    Foo(vec, FunctionArgTag{});     // OK, 3
    Foo(vec, NotInSignatureTag{});  // OK, signature
}
