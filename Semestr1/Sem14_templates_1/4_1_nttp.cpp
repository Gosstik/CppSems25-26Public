#include <array>
#include <iostream>

// Non Template Type Parameters

template <typename T, size_t N = 2>
struct Array {
    T buf[N];
};

template <typename T>
struct Array<T, 10> {
    int val;
};

int main() {
    {
        std::array<int, 10> arr = {1, 2, 3};
        for (size_t i = 0; i < arr.size(); ++i) {  // NOLINT
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
    }

    {
        int size = 5;                // not a compile time constant
        std::array<int, size> arr1;  // CE

        // const int csize = size;
        const int csize = 5;
        std::array<int, csize> arr2;  // OK

        constexpr int cesize = 15;
        std::array<int, cesize> arr3;  // OK
    }

    int var;
    std::cin >> var;
    Array<int, var> a;
}
