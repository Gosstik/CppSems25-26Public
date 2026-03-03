#include <fstream>
#include <string>

// std::basic_fstream (see inheritance)
// https://en.cppreference.com/w/cpp/io/basic_fstream

// std::ifstream and std::ofstream

// Manipulators: https://en.cppreference.com/w/cpp/io/manip

int main() {
    std::string text;
    std::ifstream istr("1_1_fstream.cpp");  // open current file
    std::ofstream ostr("codegen.cpp");
    while (istr >> text) {
        // use std::getline
        ostr << text << '\n';
    }
}
