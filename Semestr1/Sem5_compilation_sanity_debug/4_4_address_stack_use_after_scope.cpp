#include <iostream>
#include <string>

int main() {
    const char* p = "start";
    {
        std::string str = "abc";  //* make it long to prevent sso
        p = str.data();
    }
    std::cout << p << '\n';
}
