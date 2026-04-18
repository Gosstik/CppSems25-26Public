#include <iostream>

struct S {
    S(int x) : x(x) { std::cout << "S(int)\n"; }
    S(const S& other) : x(other.x) { std::cout << "S(copy)\n"; }
    S(S&& other) : x(other.x) { std::cout << "S(move)\n"; }
    ~S() { std::cout << "~S()\n"; }

    S& operator+=(const S& other) {
        x += other.x;
        return *this;
    }

    int x;
};

S operator+(const S& lhs, const S& rhs) {
    S res(lhs);
    res += rhs;
    return res;  // NRVO
}

// // Ambiguous for rvalue
// S operator+(S lhs, const S& rhs) {
//   lhs += rhs;
//   return lhs;
// }

// S operator+(S&& lhs, const S& rhs) {
//     lhs += rhs;
//     return lhs; // x2 move
// }

void Foo(const int&) {}
void Foo(int&) {}
void Foo(int&&) {}

int main() {
    // S sum = S(1) + S(2);

    S s2 = S(2);
    std::cout << "---------\n";
    S s1 = S(1) + s2;  // S(int) + S(move) vs S(int) + S(copy) with NRVO

    // int x;
    // Foo(1);
}
