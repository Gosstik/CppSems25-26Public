#include <iostream>

// NOLINTBEGIN

// OK, all are equal, but they are all declarations
void Foo(int a[10]);
void Foo(int a[]);
void Foo(int* a);


// OK, first definition
void Foo(int* a) {  // 1
  std::cout << 1;
  std::cout << sizeof(a) << '\n';
}

// CE, second definition (redefinition)
void Foo(int a[3]) {  // 2
  std::cout << 2;
  std::cout << sizeof(a) << '\n';
}

// Also CE
void Foo(int a[]) {  // 3
  std::cout << 2;
  std::cout << sizeof(a) << '\n';
}

int main() {
  // 1 == 2 == 3 --- all are pointers to int
  // Rule: when function accepts array, array to pointer conversion occurs
}

// NOLINTEND
