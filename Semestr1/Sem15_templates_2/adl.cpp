#include <iostream>

// ADL - Argument-dependent (name) lookup
// Other names: Koenig lookup

typedef int Foo;  // uncomment it !!!

namespace N {

struct A {
    explicit operator int() {
        std::cout << "N::A\n";
        return 5;
    }
};

int Foo(A val) {
    std::cout << "f(A val)\n";
    return 10;
}

}  // namespace N

int Bar(N::A a) {
    int i = Foo(a);
    return i;
}

int main() {
    std::cout << Bar(N::A()) << '\n';

    // operator<<(std::cout, 1);
    // std::cout << 1 << '\n';
}
