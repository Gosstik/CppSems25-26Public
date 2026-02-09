#include <cerrno>  // errno
#include <cmath>   // log
#include <cstdio>  // perror
#include <iostream>

// https://en.cppreference.com/w/cpp/error/errno
// Man: https://man7.org/linux/man-pages/man3/errno.3.html

// strerror() gives string printed by perror()
// errno constants: /usr/include/asm-generic/errno-base.h

void Foo() {
    EDOM;  // to look for other errno contents
}

int main() {
    double not_a_number = log(-1.0);  // Numerical argument out of domain
    // double not_a_number = log(0);  // Numerical result out of range
    if (errno != 0) {
        perror("log failed");
        std::cout << "errno: " << errno << '\n';
    }
    std::cout << not_a_number << '\n';
}
