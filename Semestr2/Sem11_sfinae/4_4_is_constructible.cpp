#include <iostream>
#include <type_traits>

class Foo {
    int v1;
    double v2;

  public:
    // Foo(int n) : v1(n), v2() {}
    Foo() = default;
    Foo(int n, double f) noexcept : v1(n), v2(f) {}
};

int main() {
    auto is = [](bool o) {
        return (o ? "is\n" : "isn't\n");
    };
    std::cout << "Foo ... "
              << is(std::is_trivially_constructible_v<Foo, int, double>);
    // std::is_constructible_v<int, int>;
}
