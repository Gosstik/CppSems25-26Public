#include <iostream>
#include <string>
#include <vector>

// v1
void Foo() {
    std::vector<std::string> strs;
    strs.reserve(3);

    strs.push_back("hello"); // ctor(c_string) + copy ctor
    strs.push_back(std::string("hello"));

    std::string tmp = "other";
    tmp += " complex ";
    tmp += "string";

    strs.push_back(tmp);
}

// v2
struct S {
  public:
    std::string data;
    S(const std::string& data) : data(data) {} // copy and possibly ctor
};

int main() {
    // v1
    Foo();

    // v2
    S s("hello");
}
