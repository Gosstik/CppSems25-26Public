#include <iostream>

// OK, CE, RE, UB ???

int main() {
    int x = 1;

    int& y = x;
    double& z = x;
    // const double& z = x;

    x = 2;

    std::cout << y << '\n'; // ???
    std::cout << z << '\n'; // ???
}
