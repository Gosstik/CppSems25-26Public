#include <algorithm>
#include <iostream>

// Descending order
bool CmpDesc(int lhs, int rhs) { return lhs > rhs; }

// Ascending order
bool CmpAsc(int lhs, int rhs) { return lhs < rhs; }

int main() {
    {
        // Motivation

        int arr[] = {2, 6, 9, 3, 5};

        std::sort(arr, arr + sizeof(arr), &CmpDesc);

        for (size_t i = 0; i < sizeof(arr); ++i) {
            std::cout << arr[i] << ' ';
        }
    }

    {
        // Declaration of pointer to function

        bool (*p)(int, int) = CmpDesc;  // function to pointer conversion
        p = CmpAsc;
        std::cout << p(1, 2) << '\n';
        // p = nullptr;

        // without cast p simply 1 or 0
        std::cout << (void*)p << '\n';
    }
}
