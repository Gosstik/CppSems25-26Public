#include <iostream>
#include <optional>

// std::optional (since C++17):
// https://en.cppreference.com/w/cpp/utility/optional

std::optional<std::string_view> GetWordInSquareBrackets(std::string_view sv) {
    size_t lpos = sv.find('[');
    if (lpos == std::string_view::npos) {
        return std::nullopt;
    }
    size_t rpos = sv.find(']', lpos + 1);
    if (rpos == std::string_view::npos) {
        return std::nullopt;
    }
    return sv.substr(lpos + 1, rpos - lpos - 1);
}

int main() {
    std::string s1("We have to parse [word] in square brackets");
    std::optional<std::string_view> w1 = GetWordInSquareBrackets(s1);
    std::cout << w1.value_or("None") << '\n';

    std::string s2("We have to parse word in square brackets");
    std::optional<std::string_view> w2 = GetWordInSquareBrackets(s2);
    std::cout << w2.value_or("<none>") << '\n';
}
