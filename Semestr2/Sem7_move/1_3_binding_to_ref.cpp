#include <iostream>
#include <string>
#include <utility>

struct S {};

int main() {
    // S s1;
    // S& s2 = static_cast<S&>(s1);
    // S&& s3 = static_cast<S&&>(s1);

    // !!! Distinguish move and binding to reference
    std::string s = "abc";
    std::string&& t = std::move(s);  // no move, just binding to reference
    std::cout << s << '\n';          // "abc"

    std::string s2 = "abc";
    std::string t2 = std::move(s2);  // Move ctor is called
    std::cout << s2 << '\n';         // ""
}
