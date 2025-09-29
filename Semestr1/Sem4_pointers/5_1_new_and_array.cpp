#include <iostream>

int main() {
    // Variable
    int* p = new int;
    delete p;

    // Initialized variable
    int* pi = new int(100);
    delete pi;

    // Array
    int* ps = new int[100];
    // int psa[100] = new int[100]; // CE
    // std::cout << ps[-2] << '\n'; // same as vector
    delete[] ps;

    // Zero filled array
    int* pza = new int[100]{};
    delete[] pza;

    // Const zero filled array (rarely used)
    const int* cpza = new int[100]{};
    delete[] cpza;
}
