#include <iostream>

// Main rule:
// ptr[ind] == *(ptr + ind)

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    std::cout << *(arr + 2) << '\n';  // Array to pointer conversion (implicit)

    int* p2 = arr + 2;  // Array to pointer conversion

    std::cout << (p2[-1] == arr[1]) << '\n';   // negative ind
    std::cout << (1 [arr] == arr[1]) << '\n';  // swap arr and ind
}
