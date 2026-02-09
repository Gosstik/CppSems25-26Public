#include <iostream>
#include <vector>

// If exception is not caught std::terminate is called
// !!! Call to dtors and buffer flushes is implementation-defined
// !!! there may be no stack unwound before std::terminate is called

struct A {
    A() { std::cout << "A\n"; }
    A(const A&) { std::cout << "A(copy)\n"; }
    ~A() {
        std::cout << "~A\n";
        // std::cout << '\n' << std::flush;
    }
};

int main() {
    A a1;
    std::vector<int> v;

    std::cout << "vector was created";
    // std::cout << '\n' << std::flush;
    // std::cout << std::endl;

    v.at(1'000'000) = 1;
    std::cout << "Ending main\n";
}
