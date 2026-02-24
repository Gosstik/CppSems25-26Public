#include <iostream>
#include <unordered_map>

// Iterators are an abstraction of pointers.

// !!! find and [] in map

template <typename T>
void Debug(T) = delete;

void IterFor(const std::unordered_map<std::string, int>& m) {
    for (auto it = m.begin(); it != m.end(); ++it) {  // NOLINT
        // auto kv = *it;
        // std::cout << kv.first << ": " << kv.second << '\n';
        std::cout << it->first << ": " << it->second << '\n';
    }
}

void RangeBasedFor(const std::unordered_map<std::string, int>& m) {
    // ! Container must define begin() and end()
    for (const auto& kv : m) {
        // Debug(kv);  // std::pair<const std::basic_string<char>, int>
        std::cout << kv.first << ": " << kv.second << '\n';
    }
}

void StructuredBindingFor(const std::unordered_map<std::string, int>& m) {
    // Will be discussed on later sems
    for (const auto& [key, value] : m) {
        std::cout << key << ": " << value << '\n';
    }
}

void OnlyValues(const std::unordered_map<std::string, int>& m) {
    // Will be discussed on later sems
    for (const auto& [_, value] : m) {
        std::cout << value << '\n';
        // std::cout << _.c_str() << '\n';
    }
}

int main() {
    std::unordered_map<std::string, int> m{
        {"Mike", 4},
        {"Alex", 10},
        {"Mary", 7},
        {"Kelly", 12},
    };

    // Debug(m.begin());
    // Debug(*m.begin());  // std::pair<const std::basic_string<char>, int>

    IterFor(m);
    std::cout << '\n';
    RangeBasedFor(m);
    std::cout << '\n';
    StructuredBindingFor(m);
    std::cout << '\n';
    OnlyValues(m);
}
