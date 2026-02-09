#include <iostream>

struct S {
    S() { std::cout << "S\n"; }

    S(const S& other) { std::cout << "copy\n"; }

    S& operator=(const S& other) {
        std::cout << "operator=\n";
        return *this;
    }

    S& operator+=(const S& rhs) {
        std::cout << "operator+=\n";
        return *this;
    }

    ~S() { std::cout << "~S\n"; }
};

// Named RVO == Named Return Value Optimization
S operator+(const S& lhs, const S& rhs) {
  S res = lhs;
  res += rhs;
  return res;
}

// S operator+(const S& lhs, const S& rhs) {
//     S res = lhs;
//     return res += rhs;
// }

int main() {
    S s1;
    S s2;
    S s3(s1 + s2);
}
