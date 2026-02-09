#include <iostream>

struct A {
    A() { std::cout << "A\n"; }
    A(const A&) { std::cout << "A(copy)\n"; }
    ~A() { std::cout << "~A\n"; }
};

int main() {
    try {
        int64_t val = 1;
        throw val;
    } catch (int64_t v) {
        try {  // OK
            v += 1;
            std::cout << "v=" << v << '\n';
            throw A();
        } catch (...) {
            std::cout << "inner catch\n";
        }
    }
}
