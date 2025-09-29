#include <iostream>

// NOLINTBEGIN

// 3 main differences:
// 1) Assignment
// 2) Addition
// 3) sizeof()

void Bar(int a[10]) {
  std::cout << sizeof(a) << '\n';  // ???
}

int main() {
    int a1[3] = {1, 2, 3};
    int a2[3] = {4, 5, 6};

    int* p1 = a1;
    int* p2 = a2;

    // Assignment
    // a1 = a2;  // CE
    p1 = p2;  // OK

    // Addition
    // a1 += 2;  // CE
    p1 += 2;  // OK

    // sizeof
    p1 = a1;
    std::cout << sizeof(a1) << ' ' << sizeof(p1) << '\n';  // ???

    // Conversion when passed to function
    Bar(a1);
    Bar(a2);
}

// NOLINTEND
