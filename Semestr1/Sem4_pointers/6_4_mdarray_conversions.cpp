#include <iostream>

void ArrayToPointerConvertion() {
    int one_dim[5] = {1, 2, 3, 4, 5};
    int* p_one = one_dim;  // array to pointer conversion
}

int main() {
    int a[5][5] = {};

    int* b[5];    // Array of 5 pointers to int
    int (*c)[5];  // Pointer to array of 5 ints

    std::cout << sizeof(b) << ' ' << sizeof(c) << '\n';

    int** ppa = a;     // CE
    int* pa[5] = a;    // CE
    int (*ap)[5] = a;  // OK, array to pointer conversion

    int** ppb = b;  // OK, array to pointer conversion
    int** ppc = c;  // CE

    int one_dim[5] = {1, 2, 3, 4, 5};
    c = &one_dim; // OK
}
