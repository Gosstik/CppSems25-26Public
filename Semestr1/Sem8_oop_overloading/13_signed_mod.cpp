#include <iostream>

// BigInteger

//  11 %  4 ==  3
//  11 % -4 ==  3
// -11 %  4 == -3
// -11 % -4 == -3

int main() {
    {
        int a = 11;
        int b = -4;
        std::cout << (a % b) << '\n';  // 3
    }

    {
        int a = -11;
        int b = 4;
        std::cout << (a % b) << '\n';  // -3
    }

    {
        int a = -11;
        int b = -4;
        std::cout << (a % b) << '\n';  // -3
    }
}
