#include <iostream>
#include <string_view>
#include <unordered_map>

// ! const may be omitted

int main() {
    std::string s1 = "one";
    const std::string_view sv1 = s1;

    std::string s2 = "two";
    const std::string_view sv2 = s2;

    std::unordered_map<std::string_view, int> m{
        {sv1, 1},
        {sv2, 2},
    };
    for (auto& [key, val] : m) {
        std::cout << key << ": " << val << '\n';
    }
    std::cout << "------------\n";

    s2 = "one";  // UB
    for (auto& [key, val] : m) {
        std::cout << key << ": " << val << '\n';
    }
    std::cout << "------------\n";

    std::string_view sv3 = "one";
    m.insert({sv3, 3});
    for (auto& [key, val] : m) {
        std::cout << key << ": " << val << '\n';
    }
    std::cout << "------------\n";

    std::cout << m["one"] << '\n';  // ???

    // sv1[0] = 'a'; // CE
}
