#include <iostream>

int main() {
    int a = 0;
    int* p = &a;
    std::cout << p << '\n';  // address

    int** pp = &p;
    std::cout << pp << '\n';  // also address
    std::cout << (*pp == p) << (**pp == a) << '\n';
}
