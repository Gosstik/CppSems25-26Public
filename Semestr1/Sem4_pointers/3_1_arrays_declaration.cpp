#include <iostream>

// NOLINTBEGIN

// Arrays declaration:
// https://en.cppreference.com/w/cpp/language/array
// Arrays initialization:
// https://en.cppreference.com/w/c/language/array_initialization

int main() {
  {
    // Array declaration

    int a1[5];
    int a2[5] = {1, 2, 3, 4, 5};
    int a3[] = {1, 2, 3, 4, 5};
    int a4[5] = {1, 2};
    int a5[5]{};
  }

  {
    // designator expression (try with g++ and clang++)

    int a[100] = {[98] = 10, [99] = 100};
    for (size_t i = 0; i < 100; ++i) {
      std::cout << a[i] << ' ';
    }
  }
}

// NOLINTEND
