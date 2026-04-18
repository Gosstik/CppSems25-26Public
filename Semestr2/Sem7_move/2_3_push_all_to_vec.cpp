#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// try on cppinsights.io

template <typename... Args>
void PushAll(std::vector<std::string>& vec, Args&&... args) {
    static_assert((... && std::is_convertible_v<Args, std::string>));
    // ... && Pack
    // Pack && ... == (T1 && ... (Tm && (Tk && Tn))...)
    // init && ... && Pack
    vec.reserve(vec.size() + sizeof...(Args));
    (..., vec.push_back(std::forward<Args>(args)));
}

int main() {
    std::vector<std::string> vec;
    std::string s = "lvalue";

    PushAll(vec);  // 0 args ???
    PushAll(vec, "abc", s, std::string(4, 'a'));

    for (auto& str : vec) {
        std::cout << str << '\n';
    }
}
