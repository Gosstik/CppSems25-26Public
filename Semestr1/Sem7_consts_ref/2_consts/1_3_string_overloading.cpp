#include <iostream>
#include <string>

void Bar(std::string& str) { std::cout << 1 << '\n'; }
void Bar(const std::string& str) { std::cout << 2 << '\n'; }

int main() {
    std::string s = "abc";
    const std::string cs = s;
    const std::string& crs = s;

    Bar(s);
    Bar(cs);
    Bar(crs);
    Bar("abc");
}
