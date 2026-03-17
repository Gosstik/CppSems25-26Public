#include <cstdio>
#include <iostream>
#include <string>
#include <string_view>

// since c++17

// Motivation: avoid unnecessary allocations
// https://en.cppreference.com/w/cpp/string/basic_string_view

static constexpr std::string_view kTableName = "order_details";  // OK, no alloc
// static constexpr std::string kTableName = "order_details"; // OK

struct MyString {
    MyString(std::string_view) {}
};

void Printer(const std::string& s) { std::cout << "Printer: " << s << '\n'; }

// !!! Do not use references for views
std::string_view GetWordInSquareBrackets(std::string_view sv) {
    sv.remove_prefix(sv.find('[') + 1);          // No allocation
    sv.remove_suffix(sv.size() - sv.find(']'));  // No allocation
    // Printer(sv); // CE
    // Printer(sv.data()); // ???
    return sv;
}

int main() {
    std::cout << kTableName << '\n';

    ////////////////////////////////////////////////////////////////////////////

    std::string s("We have to parse [word] in square brackets");
    std::string_view sv("We have to parse [word] in square brackets");  // OK
    // ...
    std::string a = sv;  // CE, ctor std::string(std::string_view) is explicit
    std::string b(sv);   // OK

    // CE - Explicit constructor is not a candidate
    const std::string& dangerous(sv);
    /// OK, but actually allocates memory - that is invalid, here simple
    /// string_view should be used instead.
    const MyString& m(sv);

    ////////////////////////////////////////////////////////////////////////////

    // std::string_view word = GetWordInSquareBrackets(s);
    std::string_view word =
        GetWordInSquareBrackets("We have to parse [word] in square brackets");
    std::cout << word << '\n';
}
