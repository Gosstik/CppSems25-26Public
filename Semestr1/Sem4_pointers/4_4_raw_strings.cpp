#include <iostream>

// NOLINTBEGIN(modernize-raw-string-literal)

int main() {
    // Raw strings
    std::cout << "print linefeed: \"\\n\"" << '\n';  // Difficult to read
    std::cout << R"(print linefeed: "\n")" << '\n';  // More elegant solution
    std::cout << R"~~~(print )linefeed(: "\n")~~~" << '\n';  // Custom sequence

    std::cout << '\n';

    // Multiline strings
    const char* multi_raw_str = R"-(Multi
line
string)-";

    std::cout << multi_raw_str << '\n';
}

// NOLINTEND(modernize-raw-string-literal)
