#include <iostream>

int main() {
    // Variable
    int* p = new int;
    // *p = 1;
    std::cout << *p << '\n';
    delete p;

    // Initialized variable
    int* pi = new int(100);
    delete pi;

    // Array
    int* ps = new int[100];
    std::cout << *ps << '\n';
    // int psa[100] = new int[100]; // CE
    // std::cout << ps[-2] << '\n'; // same as vector
    delete[] ps;

    // Dynamic size
    int n{};
    std::cin >> n;
    int* psn = new int[n];
    delete[] psn;

    // Zero filled array
    int* pza = new int[100]{};
    delete[] pza;

    // Const zero filled array (rarely used)
    const int* cpza = new int[100]{};
    delete[] cpza;
}
