#include <exception>
#include <iostream>
#include <string>

struct S : std::exception {
    explicit S(std::string data) : data(std::move(data)) {
        std::cout << "S(string)\n";
    }
    S(const S& other) : data(other.data) { std::cout << "S(const S&)\n"; }
    // S(S&& other) noexcept: data(std::move(other.data)) {
    //   std::cout << "S(S&&)\n";
    //   throw "bad luck!\n";
    // }
    S(S&& other) = delete;

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
    try {
        S s("1234567890");
        // throw s;
        throw S(s);
    } catch (const S& e) {
        std::cout << "e.data=" << e.data << '\n';
    }
}
