#include <iostream>

// try with -fsanitize=address

struct S {
    S(int x) : p(new int(x)) {  // NOLINT
        std::cout << "S\n";
        throw std::runtime_error("re");
    }
    ~S() {
        std::cout << "~S\n";
        delete p;
    }

    int* p;
};

int main() {
    try {
        S s(1);
    } catch (...) {
        std::cout << "caught!\n";
    }
}
