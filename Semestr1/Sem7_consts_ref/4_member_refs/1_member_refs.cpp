#include <iostream>

// Member initializer list

struct S {
    int& r;

    S(int& r) : r(r) {
        // other code...
    }
};

int main() {
    int x = 1;
    S s(x);
    ++s.r;
    std::cout << x << s.r;
}
