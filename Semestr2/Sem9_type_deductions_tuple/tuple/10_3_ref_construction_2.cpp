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
    {
        // from ref to val
        S s;

        std::cout << "-----\n";

        std::tuple<S&, int> t1(s, 10);  // ???

        std::cout << "-----\n";

        std::tuple<S, int> t2(t1);             // OK
        std::tuple<S, int> t3(std::move(t1));  // OK
    }

    {
        // from val to ref
        S s;

        std::cout << "-----\n";

        std::tuple<S, int> t1(s, 10);  // ???

        std::cout << "-----\n";

        std::tuple<S&, int> t2(t1);             // OK
        std::tuple<S&, int> t3(std::move(t1));  // CE
    }

    //// !!! operator=() works in the same way
}
