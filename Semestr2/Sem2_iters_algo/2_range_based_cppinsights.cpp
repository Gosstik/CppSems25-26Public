#include <iostream>
#include <unordered_map>

// Use cppinsights

int main() {
    std::unordered_map<std::string, int> m;

    for (const auto& kv : m) {
        std::cout << kv.first << ": " << kv.second << '\n';
    }
}
