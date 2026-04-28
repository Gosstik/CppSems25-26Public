#include <iostream>
#include <tuple>

struct S {
    S() { std::cout << "S()" << std::endl; }
    S(const S&) { std::cout << "S(const S&)" << std::endl; }
    S(S&&) { std::cout << "S(S&&)" << std::endl; }
    S& operator=(const S&) {
        std::cout << "operator=(const S&)" << std::endl;
        return *this;
    }
    S& operator=(S&&) {
        std::cout << "operator=(S&&)" << std::endl;
        return *this;
    }
    ~S() { std::cout << "~S()" << std::endl; }
};

int main() {
    S s;
    S lr;
    S rr;

    std::cout << "-----\n";

    std::tuple<S, S&, S&&> t1(s, lr, std::move(rr));  // ???

    std::cout << "-----\n";

    //   std::tuple t2(t1); // CE, t1 contains rvalue references
    std::tuple t2(std::move(t1));  // ???
}
