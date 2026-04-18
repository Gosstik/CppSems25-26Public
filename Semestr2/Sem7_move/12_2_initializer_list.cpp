#include <iostream>
#include <string>
#include <vector>

struct S {
    S(std::string data) : data(std::move(data)) { std::cout << "S(string)\n"; }
    S(const S& other) : data(other.data) { std::cout << "S(const S&)\n"; }
    S(S&& other) noexcept : data(std::move(other.data)) {
        std::cout << "S(S&&)\n";
    }
    S& operator=(const S& other) {
        data = other.data;
        std::cout << "operator=(const S&)\n";
        return *this;
    }
    S& operator=(S&& other) noexcept {
        data = std::move(other.data);
        std::cout << "operator=(S&&)\n";
        return *this;
    }

    std::string data;
};

int main() {
    S s1{"hello"};
    std::cout << "---------\n";
    std::vector<S> v{s1, std::string("abc"), s1};  // out ???
    // std::vector<S> v{s1, s1};  // out ???
    std::cout << "---------\n";
    for (auto& e : v) {
        std::cout << e.data << '\n';
    }
}
