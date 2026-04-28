#include <iostream>
#include <tuple>
#include <unordered_map>

struct ignore_t {
    template <typename T>
    void operator=(const T&) {}
};

ignore_t ignore;

int main() {
    std::unordered_map<std::string, int> m{
        {"Moscow", 50},
        {"Lipetsk", 48},
        {"Amur", 28},
        {"Smolensk", 67},
    };

    auto it = m.begin();

    auto& [key, value] = *it;
    std::cout << key << ": " << value << '\n';

    ++it;

    std::tie(std::ignore, value) = *it;
    std::cout << value << '\n';

    {
        std::tuple<int, double, char> t{1, 2.0, 'a'};
        auto [_, _, symbol] = t;  // since c++26
        std::cout << symbol << '\n';
    }
}
